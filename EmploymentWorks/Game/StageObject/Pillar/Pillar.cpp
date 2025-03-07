/*
	@file	Pillar.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Pillar.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
Pillar::Pillar(CommonResources* resources)
	:
	MoveEntity(resources,Vector3::One,Vector3::Zero,Quaternion::Identity)
	,m_initialScale{}
	
{
	BaseEntity::SetIsEntityActive(false);
}

/// <summary>
/// デストラクタ
/// </summary>
Pillar::~Pillar()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void Pillar::Initialize()
{
	MoveEntity::Initialize();

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Beam.cmo", *fx);

	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), 2.0f);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), BaseEntity::GetScale());

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void Pillar::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//オブジェクトか描画が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}


	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	MoveEntity::Render(view, projection);

	//モデルの描画
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection);

	//m_bounding->DrawBoundingSphere(view, projection);
	CollisionEntity::GetBounding()->DrawBoundingBox(BaseEntity::GetPosition(), view, projection);



}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Pillar::Update(const float& elapsedTime)
{

	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}


}

void Pillar::AddCollision(CollisionManager* collsionManager)
{
}

void Pillar::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
}




void Pillar::ChangeState(IState* nextState)
{
}






