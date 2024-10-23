/*
	@file	Player.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Player.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Object/Enemy/Enemy.h"
#include "Libraries/MyLib/Bounding.h"
#include "Game/DetectionCollision/CollisionManager.h"

#include "Libraries/MyLib/Camera/TPS_Camera.h"

const float MOVE_SPEED = 5.0f;                                        //動く時のスピード
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION( 0.0f,0.0f,-1.0f); //初期の向いている方向

const DirectX::SimpleMath::Vector3 EYE_TO_POSITION_DIFFERENCE(0.0f, 0.7f, 0.0f); //座標と目の座標の差分

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Player::Player()
	:
	m_commonResources{},
	m_model{},
	m_position{},
	m_direction{INITIAL_DIRECTION},
	m_enemy{ },
	m_graivty{},
	m_isLockOn{}
	,m_currentState{}
	,m_hp{}
	,m_boomerangIndex{}
	,m_scrollWheelValue{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Player::~Player()
{
	// do nothing.



}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Player::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position)
{
	using namespace DirectX::SimpleMath;

	assert(resources);
	m_commonResources = resources;

	


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();




	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/NewPlayer.cmo", *fx);

	m_position = position;
	m_eyePosition = m_position + EYE_TO_POSITION_DIFFERENCE;
	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.4f, 0.8f, 0.4f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 1.0f);

	//ストック
	for (auto& boomerang : m_boomerang)
	{
		boomerang->Initialize(m_commonResources);
	}



	m_usually->Initialize();
	m_usually->SetResouces(m_commonResources);

	m_blownAway->Initialize();

	m_currentState = m_usually.get();


	m_graivty = 0.05f;
	m_isLockOn = false;

	m_isJump = false;
	m_hp = 3;
	
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);;

	m_boomerangIndex = 0;

	m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Have);

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	const auto& state = m_commonResources->GetInputManager()->GetMouseState();

	//所持しているブーメランがStock状態なら
	if (m_boomerang[m_boomerangIndex]->GetUseState() == Boomerang::UseState::Stock)
	{
		m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Have);
	}

	// マウスのホイール値を取得
	m_scrollWheelValue = state.scrollWheelValue;

	if (m_scrollWheelValue > 0)
	{
		//変更前のブーメラン
		switch (m_boomerang[m_boomerangIndex]->GetUseState())
		{

			case Boomerang::UseState::Stock:
				break;
			case Boomerang::UseState::Have:
			case Boomerang::UseState::GetReady:
				m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Stock);
				m_boomerang[m_boomerangIndex]->ChangeState(m_boomerang[m_boomerangIndex]->GetBoomerangIdling());
				break;
			case Boomerang::UseState::Throw:
				break;
			default:
				break;
		}

		//使用中のブーメランを切り替える
		m_boomerangIndex++;
		m_boomerangIndex = std::min(m_boomerangIndex, 2);

		switch (m_boomerang[m_boomerangIndex]->GetUseState())
		{

			case Boomerang::UseState::Stock:
				m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Have);
				break;
			case Boomerang::UseState::Have:
			
				break;
			case Boomerang::UseState::GetReady:
				break;
			case Boomerang::UseState::Throw:
				break;
			default:
				break;
		}

		Mouse::Get().ResetScrollWheelValue();

	}
	if (m_scrollWheelValue < 0)
	{

		//変更前のブーメラン
		switch (m_boomerang[m_boomerangIndex]->GetUseState())
		{

			case Boomerang::UseState::Stock:
				break;
			case Boomerang::UseState::Have:
			case Boomerang::UseState::GetReady:
				m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Stock);
				m_boomerang[m_boomerangIndex]->ChangeState(m_boomerang[m_boomerangIndex]->GetBoomerangIdling());

				break;
			case Boomerang::UseState::Throw:
				break;
			default:
				break;
		}

		m_boomerangIndex--;
		m_boomerangIndex = std::max(m_boomerangIndex, 0);

		switch (m_boomerang[m_boomerangIndex]->GetUseState())
		{

			case Boomerang::UseState::Stock:
				m_boomerang[m_boomerangIndex]->SetUseState(Boomerang::UseState::Have);
				break;
			case Boomerang::UseState::Have:
				break;
			case Boomerang::UseState::GetReady:
				break;
			case Boomerang::UseState::Throw:
				break;
			default:
				break;
		}



		Mouse::Get().ResetScrollWheelValue();



	}

	m_currentState->Update(elapsedTime);
	//目の座標の更新
	m_eyePosition = m_position + EYE_TO_POSITION_DIFFERENCE;


	for (auto& boomerang : m_boomerang)
	{
		boomerang->Update(elapsedTime);

	}



	for(std::unique_ptr<Boomerang>& boomerang : m_boomerang)
	{


		//ブーメランが落ちているなら
		if(boomerang->GetBoomerangState() == boomerang->GetBoomerangDrop())
		{

			float distance = DirectX::SimpleMath::Vector3::Distance(boomerang->GetPosition(), m_position);

			if(distance <= 1)
			{

				const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

				if (kbTracker->released.F)
				{

					boomerang->ChangeState(boomerang->GetBoomerangIdling());

					boomerang->SetUseState(Boomerang::UseState::Stock);

				}
			}
		}
	}

	m_bounding->Update(m_position);

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Player::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{

	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	//	半透明描画指定
	//ID3D11BlendState* blendstate = states->NonPremultiplied();

	//// モデルを描画する
	//m_model->Draw(context, *states, m_currentState->GetMatrix(), view, projection,
	//	false,
	//	[&]()
	//	{

	//		//DirectX::Colors::White.v;

	//		//DirectX::FXMVECTOR colorValues {1.0f, 1.0f, 1.0f, 0.5f};

	//		//m_basicEffect->SetDiffuseColor(colorValues);

	//		//// ブレンドステートを設定する
	//		//context->OMSetBlendState(blendstate, nullptr, 0xffffffff);

	//		//context->OMSetDepthStencilState(states->DepthDefault(), 0);

	//		//	シェーダの登録を解除しておく
	//		//context->PSSetShader(nullptr, nullptr, 0);

	//	}
	//);
	
	m_model->Draw(context, *states, m_currentState->GetMatrix(), view, projection);
	//m_bounding->DrawBoundingBox(m_position, view, projection);
	//m_bounding->DrawBoundingSphere(m_position, view, projection);

	for (auto& boomerang : m_boomerang)
	{

		//使用しているブーメラン
		if (boomerang->GetUseState() != Boomerang::UseState::Stock)
		{

			boomerang->Render(view, projection);


		}

	}

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Player::Finalize()
{
	// do nothing.
}

void Player::ChangeState(IPlayerState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}


void Player::RegistrationInformation(Enemy* enemy, mylib::TPS_Camera* tps_Camera)
{
	m_enemy = enemy;
	m_tpsCamera = tps_Camera;

	m_usually->RegistrationInformation(this);
	m_blownAway->RegistrationInformation(this);


	//ストック
	for (auto& stock : m_boomerang)
	{
		stock->RegistrationInformation(this, m_enemy);
	}

}

void Player::Instances()
{

	//m_usingBoomerang = std::make_unique<Boomerang>();
	m_bounding = std::make_unique<Bounding>();
	m_usually = std::make_unique<PlayerUsually>();
	m_blownAway = std::make_unique<PlayerBlownAway>();

	
	//ストックのブーメラン
	for (int i = 0; i < 3; i++)
	{
		auto stock = std::make_unique<Boomerang>();
		stock->Instances();
		m_boomerang.push_back(std::move(stock));

	}

}

void Player::DemandBlownAwayDirection(DirectX::SimpleMath::Vector3 pos)
{

	m_blownAwayDirection = m_position - pos;

	m_blownAwayDirection.Normalize();

	//m_position += m_blownAwayDirection;
}




void Player::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	//m_usingBoomerang->RegistrationCollionManager(collsionManager);

	for (auto& boomerang : m_boomerang)
	{
		boomerang->RegistrationCollionManager(collsionManager);
	}
}


void Player::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(Pos);

	//動く簿部ジェクトのタグを
	switch (PartnerTag)
	{
		case CollsionObjectTag::Floor:

			if (m_currentState == m_blownAway.get())
			{
				ChangeState(m_usually.get());
			}
			m_isJump = false;
			break;
		default:
			break;
	}


}
