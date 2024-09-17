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
//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Player::Player()
	:
	m_commonResources{},
	m_model{},
	m_position{},
	m_direction{INITIAL_DIRECTION},
	m_boomerang{},
	m_enemy{ },
	m_graivty{},
	m_isLockOn{}
	,m_currentState{}
	,m_hp{}
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


	m_boomerang->Initialize(m_commonResources);

	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.4f, 0.8f, 0.4f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 1.0f);

	m_usually->Initialize();

	m_blownAway->Initialize();

	m_currentState = m_usually.get();


	m_graivty = 0.05f;
	m_isLockOn = false;

	m_hp = 1;

	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);;



}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Player::Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	UNREFERENCED_PARAMETER(cameraRotation);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	m_currentState->Update(elapsedTime);

	m_boomerang->Update(elapsedTime);

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Player::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	//	半透明描画指定
	ID3D11BlendState* blendstate = states->NonPremultiplied();

	// モデルを描画する
	m_model->Draw(context, *states, m_currentState->GetMatrix(), view, projection,
		false,
		[&]()
		{

			DirectX::Colors::White.v;

			DirectX::FXMVECTOR colorValues {1.0f, 1.0f, 1.0f, 0.5f};

			m_basicEffect->SetDiffuseColor(colorValues);

			// ブレンドステートを設定する
			context->OMSetBlendState(blendstate, nullptr, 0xffffffff);

			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			//	シェーダの登録を解除しておく
			//context->PSSetShader(nullptr, nullptr, 0);

		}
	);
	m_bounding->DrawBoundingBox(m_position, view, projection);
	m_bounding->DrawBoundingSphere(m_position, view, projection);

	m_boomerang->Render(view, projection);



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


void Player::RegistrationInformation(Enemy* enemy)
{
	m_enemy = enemy;

	m_boomerang->RegistrationInformation(this, m_enemy);
	m_usually->RegistrationInformation(m_boomerang.get(), this);
	m_blownAway->RegistrationInformation(m_boomerang.get(), this);

}

void Player::Instances()
{

	m_boomerang = std::make_unique<Boomerang>();
	m_bounding = std::make_unique<Bounding>();
	m_usually = std::make_unique<PlayerUsually>();
	m_blownAway = std::make_unique<PlayerBlownAway>();

	m_boomerang->Instances();
	
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
	m_boomerang->RegistrationCollionManager(collsionManager);
}


void Player::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(Pos);

	//動く簿部ジェクトのタグを
	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:
			break;
		case CollsionObjectTag::Player:
			break;
		case CollsionObjectTag::Enemy:
			break;
		case CollsionObjectTag::NotMoveObject:
			break;
		case CollsionObjectTag::None:
			break;
		case CollsionObjectTag::Wall:
			break;
		case CollsionObjectTag::Floor:

			if (m_currentState == m_blownAway.get())
			{
				ChangeState(m_usually.get());
			}

			break;
		default:
			break;
	}


}
