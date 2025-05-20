/*
	@file	Floor.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Floor.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/GameResources.h"


#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"



/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
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


/// <summary>
/// 初期化
/// </summary>
void Floor::Initialize()
{

	INotMoveEntity::Initialize();


	// モデルを読み込む
	m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("Floor");

	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), BaseEntity::GetScale());

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
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

	//当たり判定の描画
	CollisionEntity::GetBounding()->DrawBoundingBox(BaseEntity::GetPosition(), view, projection);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Floor::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}


}





