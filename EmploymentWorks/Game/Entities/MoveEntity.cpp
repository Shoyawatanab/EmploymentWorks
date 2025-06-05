#include "pch.h"
#include "MoveEntity.h"
#include "Libraries/WataLib/Bounding.h"
#include "GameBase/Manager/CollisiionManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
MoveEntity::MoveEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	CollisionEntity(resources, scale,position,rotation)
{



}

/// <summary>
/// デストラクタ
/// </summary>
MoveEntity::~MoveEntity()
{
}

/// <summary>
/// 初期化
/// </summary>
void MoveEntity::Initialize()
{

	CollisionEntity::Initialize();

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void MoveEntity::Update(const float& elapsedTime)
{

	CollisionEntity::Update(elapsedTime);

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void MoveEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	CollisionEntity::Render(view, projection);

}


/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void MoveEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	CollisionEntity::OnCollisionEnter(object, tag);

}
