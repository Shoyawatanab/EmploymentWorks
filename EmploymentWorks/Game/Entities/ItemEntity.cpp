#include "pch.h"
#include "ItemEntity.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Animation.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
ItemEntity::ItemEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	MoveEntity(resources, scale,position,rotation)
{


}

/// <summary>
/// デストラクタ
/// </summary>
ItemEntity::~ItemEntity()
{
}



/// <summary>
/// 初期化
/// </summary>
void ItemEntity::Initialize()
{

	MoveEntity::Initialize();

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void ItemEntity::Update(const float& elapsedTime)
{

	MoveEntity::Update(elapsedTime);


}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void ItemEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	MoveEntity::Render(view, projection);

}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void ItemEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	MoveEntity::OnCollisionEnter(object, tag);

}
