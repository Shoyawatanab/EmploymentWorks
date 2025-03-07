#include "pch.h"
#include "CollisionEntity.h"
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
CollisionEntity::CollisionEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	BaseEntity(resources, scale, position, rotation)
{

	m_bounding = std::make_unique<WataLib::Bounding>(resources);

}


/// <summary>
/// 初期化
/// </summary>
void CollisionEntity::Initialize()
{

	BaseEntity::Initialize();

	m_bounding->Initialize();

	//どの当たり判定を生成するかは派生クラスで定義

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void CollisionEntity::Update(const float& elapsedTime)
{

	BaseEntity::Update(elapsedTime);

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void CollisionEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	BaseEntity::Render(view, projection);

	m_bounding->Draw(BaseEntity::GetPosition(), BaseEntity::GetRotation(), view, projection);


}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void CollisionEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

}

/// <summary>
/// 当たり判定クラスに追加
/// </summary>
/// <param name="collsionManager">当たり判定クラス</param>
void CollisionEntity::AddCollision(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}

