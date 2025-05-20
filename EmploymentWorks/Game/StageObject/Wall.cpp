/*
	@file	Wall.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Wall.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/GameResources.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
Wall::Wall(CommonResources* resources
	,DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation)
	:
	m_model{}
	,INotMoveEntity(resources,scale,position,rotation)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Wall::~Wall()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void Wall::Initialize()
{
	using namespace DirectX::SimpleMath;

	INotMoveEntity::Initialize();


	// モデルを読み込む
	m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("Wall");

	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), 50.0f);

	//回転を含めた範囲を求める
	Vector3 Extents = Vector3::Transform(BaseEntity::GetScale(), BaseEntity::GetRotation());
	//AABBでマイナスだとダメだから
	Extents.x = std::abs(Extents.x);
	Extents.y = std::abs(Extents.y);
	Extents.z = std::abs(Extents.z);

	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Extents);

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void Wall::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
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


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Wall::Update(const float& elapsedTime)
{

	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	INotMoveEntity::Update(elapsedTime);


}







//---------------------------------------------------------
