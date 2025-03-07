/*
	@file	Floor.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Floor.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"

using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Floor::Floor(CommonResources* resources
	,DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation)
	:
	m_model{}
	,INotMoveEntity(resources,scale,position,rotation)
{

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Floor::~Floor()
{
	// do nothing.
}




void Floor::Initialize()
{

	INotMoveEntity::Initialize();

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Floor.cmo", *fx);

	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), BaseEntity::GetScale());

}

void Floor::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//オブジェクトか描画が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}




	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	INotMoveEntity::Render(view, projection);

	//モデルの描画
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection);

	//m_bounding->DrawBoundingSphere(view, projection);
	CollisionEntity::GetBounding()->DrawBoundingBox(BaseEntity::GetPosition(), view, projection);
}

void Floor::Update(const float& elapsedTime)
{
	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}


}

void Floor::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
	INotMoveEntity::OnCollisionEnter(object, tag);
}




void Floor::SetDatas(DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation)
{



}


//---------------------------------------------------------
