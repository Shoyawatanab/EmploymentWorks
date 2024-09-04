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
#include "Game/Object/Player.h"
#include "Libraries/MyLib/Bounding.h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Game/Object/Boomerang/BoomerangOrbit.h"


const float SCALE = 0.5f; //オブジェクトの大きさ


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Boomerang::Boomerang(Player* player, Enemy* enemy)
	:
	m_player{player},
	m_commonResources{},
	m_model{},
	m_position{},
	m_currentState{},
	m_idling{},
	m_throw{},
	m_scale{},
	m_enemy{ enemy },
	m_orbit{}
	, m_repelled{}
	, m_previousFramePos{}
	, m_drop{}

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
	
	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Boomerang.cmo", *fx);


	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

	m_idling = std::make_unique<BoomerangIdling>(this,m_player);
	m_idling->Initialize();
	m_throw = std::make_unique<BoomerangThrow>(this,m_player,m_enemy);
	m_throw->Initialize();
	m_getReady = std::make_unique<BoomerangGetReady>(this, m_player);
	m_getReady->Initialize();

	m_repelled = std::make_unique<BoomerangRepelled>(this);
	m_repelled->Initialize();

	m_drop = std::make_unique<BoomerangDrop>(this);
	m_drop->Initialize();


	m_currentState = m_idling.get();
	
	m_position = m_player->GetPosition();
	m_scale = SCALE;

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.3f, 0.5f, 0.3f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 0.7f);

	m_orbit = std::make_unique<BoomerangOrbit>(this, m_player, m_enemy);
	m_orbit->Initialize(m_commonResources);

	m_onCollisionTag = CollsionObjectTag::None;

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
	m_bounding->DrawBoundingSphere(m_position, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);

	if (m_currentState == m_getReady.get())
	{
		m_orbit->Render();

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


void Boomerang::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{

	switch (PartnerTag)
	{
		case CollsionObjectTag::Player:
			break;
		case CollsionObjectTag::Enemy:
			break;
		case CollsionObjectTag::Boomerang:
			break;
		case CollsionObjectTag::None:
			break;
		case CollsionObjectTag::Floor:
			ChangeState(m_drop.get());
			break;
		case CollsionObjectTag::NotMoveObject:

			if (m_currentState == m_throw.get())
			{
				//弾かれる処理に切り替え
				ChangeState(m_repelled.get());

			}
			break;
		case CollsionObjectTag::Wall:

			if (m_currentState == m_throw.get())
			{
				ChangeState(m_repelled.get());

			}
			break;
		default:
			break;
	}



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
