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


const float SCALE = 0.5f; //オブジェクトの大きさ


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Boomerang::Boomerang(Player* player)
	:
	m_player{player},
	m_commonResources{},
	m_model{},
	m_boundingSphere{},
	m_position{},
	m_currentState{},
	m_idling{},
	m_throw{},
	m_scale{}
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

	m_boundingSphere = CreateBoundingSphere(1.0f);

	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);

	m_idling = std::make_unique<BoomerangIdling>(this,m_player);
	m_idling->Initialize();
	m_throw = std::make_unique<BoomerangThrow>(this,m_player);
	m_throw->Initialize();

	m_currentState = m_idling.get();
	
	//m_position = m_player->GetPosition();
	m_scale = SCALE;
	//m_rotate = m_player->GetRotate();


}


//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Boomerang::Update(float elapsedTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsedTime);


	m_currentState->Update(elapsedTime);

	m_boundingSphere.Center = Vector3(0, 0, 0);
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

	


	// プリミティブ描画を開始する
	m_primitiveBatch->Begin();
#ifdef _DEBUG
	DirectX::XMVECTOR color = DirectX::Colors::Yellow;

	// 砲塔の境界球を描画する
	DX::Draw(m_primitiveBatch.get(), m_boundingSphere, color);


#endif
	// プリミティブ描画を終了する
	m_primitiveBatch->End();


	// デバッグ情報を表示する
	auto debugString = m_commonResources->GetDebugString();
	//debugString->AddString("Rotate : %f", m_rotate.x);
	debugString->AddString("BoomeerangSpherePos : %f, %f, %f", m_position.x, m_position.y, m_position.z);
	debugString->AddString("BoomerangRotate : %f, %f, %f", m_rotate.x, m_rotate.y, m_rotate.z);

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





// 線形補間を行う
DirectX::SimpleMath::Vector3 Lerp(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end, const float& t)
{
	return (1.0f - t) * start + t * end;
}

DirectX::BoundingSphere Boomerang::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere turretBoundingSphere;
	// 境界球の半径を設定する
	turretBoundingSphere.Radius = radius;
	// 境界球を返す
	return turretBoundingSphere;
}
