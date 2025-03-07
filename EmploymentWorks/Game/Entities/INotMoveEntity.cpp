#include "pch.h"
#include "INotMoveEntity.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
INotMoveEntity::INotMoveEntity(CommonResources* resources
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
INotMoveEntity::~INotMoveEntity()
{
}

/// <summary>
/// 初期化
/// </summary>
void INotMoveEntity::Initialize()
{

	CollisionEntity::Initialize();

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
void INotMoveEntity::Update(const float& elapsedTime)
{

	CollisionEntity::Update(elapsedTime);

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void INotMoveEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	CollisionEntity::Render(view, projection);

}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void INotMoveEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	CollisionEntity::OnCollisionEnter(object, tag);

}
