/*
	@file	Boomerang.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Boomerang.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Libraries/Microsoft/DebugDraw.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Bounding.h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Game/Object/Boomerang/BoomerangOrbit.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Observer/Messenger.h"


const float SCALE = 4.0f; //オブジェクトの大きさ


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Boomerang::Boomerang()
	:
	m_player{},
	m_commonResources{},
	m_model{},
	m_position{},
	m_currentState{},
	m_idling{},
	m_throw{},
	m_scale{},
	m_enemy{},
	m_orbit{}
	, m_repelled{}
	, m_previousFramePos{}
	, m_drop{}
	,m_onCollisionTag{}
	,m_useState{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Boomerang::~Boomerang()
{
	// do nothing.

}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Boomerang::Initialize(CommonResources* resources)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Boomerang.cmo", *fx);


	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

	m_idling->Initialize();
	m_throw->Initialize();
	m_getReady->Initialize();

	m_repelled->Initialize();

	m_drop->Initialize();


	m_currentState = m_idling.get();
	
	m_position = m_player->GetPlayerEyePosition();
	m_scale = SCALE;

	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.5f, 0.1f, 0.5f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 0.9f);

	m_orbit = std::make_unique<BoomerangOrbit>(this, m_player, m_enemy,m_playScene);
	m_orbit->Initialize(m_commonResources);

	m_onCollisionTag = CollsionObjectTag::None;

	m_useState = UseState::Stock;

	m_enemyHitTime = 0;

	m_isEnemyHit = false;

	// 影を作成する
	m_shadow = std::make_unique<Shadow>();
	m_shadow->Initialize(device, context, states);


}


//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Boomerang::Update(float elapsedTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsedTime);



	m_previousFramePos = m_position;

	m_currentState->Update(elapsedTime);

	if (m_currentState == m_getReady.get())
	{
		m_orbit->Update(elapsedTime);

	}

	m_bounding->Update(m_position);


	if (m_enemyHitTime >= 4.0f)
	{
		m_isEnemyHit = false;

		return;
	}

	if (m_isEnemyHit)
	{
		m_enemyHitTime += elapsedTime;
	}

	

}


//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Boomerang::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();
	

	// モデルを描画する
	m_model->Draw(context, *states, m_currentState->GetMatrix(), view, projection);
	//m_bounding->DrawBoundingSphere(m_position, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);

	if (m_currentState == m_getReady.get() && m_player->GetIsOrbit())
	{
		m_orbit->Render(view,projection);

	}

	if (m_useState == UseState::Throw)
	{
		DirectX::SimpleMath::Vector3 shadowPos = m_position;
		shadowPos.y = 0.1f;

		// 自機の影を描画する
		m_shadow->Render(context, states, view, projection, shadowPos, 0.5f);

	}

	// プリミティブ描画を開始する


	//// デバッグ情報を表示する
	//auto debugString = m_commonResources->GetDebugString();
	////debugString->AddString("Rotate : %f", m_rotate.x);
	//debugString->AddString("BoomeerangSpherePos : %f, %f, %f", m_position.x, m_position.y, m_position.z);
	//debugString->AddString("BoomerangRotate : %f, %f, %f", m_rotate.x, m_rotate.y, m_rotate.z);

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Boomerang::Finalize()
{
	// do nothing.
}

void Boomerang::ChangeState(IBoomerangState* nextState)
{
	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();
}

void Boomerang::DemandBounceDirection(DirectX::SimpleMath::Vector3 pos, CollsionObjectTag& tag)
{
	UNREFERENCED_PARAMETER(pos);


	switch (tag)
	{
		case CollsionObjectTag::None:
			break;
		case CollsionObjectTag::Player:
			break;
		case CollsionObjectTag::Enemy:
			break;
		case CollsionObjectTag::Boomerang:
			break;
		case CollsionObjectTag::Pillar:
		case CollsionObjectTag::Stage:
			m_bounceDirection = m_previousFramePos - m_position;
			break;
		case CollsionObjectTag::Floor:
			break;
		default:
			break;
	}


}


void Boomerang::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{

	switch (PartnerTag)
	{
		case CollsionObjectTag::Floor:
			if (m_currentState == m_repelled.get())
			{
				ChangeState(m_drop.get());
			}
			if (m_currentState == m_throw.get())
			{
				ChangeState(m_repelled.get());
			}

			break;
		case CollsionObjectTag::Pillar:
		case CollsionObjectTag::Stage:
			DemandBounceDirection(Pos, PartnerTag);
			if (m_currentState == m_throw.get())
			{
				ChangeState(m_repelled.get());
			}
			break;
		case CollsionObjectTag::EnemyParts:
			if (!m_isEnemyHit)
			{
				m_isEnemyHit = true;
				Messenger::Notify2(Messenger::CREATEHITEFFECTS, m_position);

			}

			break;
		default:
			break;
	}



}

void Boomerang::RegistrationInformation(Player* player, Enemy* enemy, PlayScene* playScene)
{

	m_player = player;
	m_enemy = enemy;
	m_playScene = playScene;

	m_idling->RegistrationInformation(this, m_player);
	m_throw->RegistrationInformation(this, m_player, m_enemy);
	m_getReady->RegistrationInformation(this, m_player);
	m_repelled->RegistrationInformation(this);
	m_drop->RegistrationInformation(this);
	
}

void Boomerang::Instances()
{

	m_idling = std::make_unique<BoomerangIdling>();
	m_throw = std::make_unique<BoomerangThrow>();
	m_getReady = std::make_unique<BoomerangGetReady>();
	m_repelled = std::make_unique<BoomerangRepelled>();
	m_drop = std::make_unique<BoomerangDrop>();
	m_bounding = std::make_unique<Bounding>();


}





// 線形補間を行う
DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}
void Boomerang::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}
