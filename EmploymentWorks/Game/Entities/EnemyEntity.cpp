#include "pch.h"
#include "EnemyEntity.h"
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
EnemyEntity::EnemyEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	CompositeEntity(resources,scale,position,rotation)
	,m_enemyMangaer{}
{


}

/// <summary>
/// デストラクタ
/// </summary>
EnemyEntity::~EnemyEntity()
{
}

/// <summary>
/// 初期化
/// </summary>
void EnemyEntity::Initialize()
{

	CompositeEntity::Initialize();

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void EnemyEntity::Update(const float& elapsedTime)
{

	CompositeEntity::Update(elapsedTime);

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void EnemyEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	CompositeEntity::Render(view, projection);

}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void EnemyEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	CompositeEntity::OnCollisionEnter(object, tag);

}

/// <summary>
/// マネージャーのポインタの追加
/// </summary>
/// <param name="enemyManager">エネミーマネージャー</param>
void EnemyEntity::SetManager(EnemyManager* enemyManager)
{

	m_enemyMangaer = enemyManager;

}
