#include "pch.h"
#include "CompositeEntity.h"
#include "Libraries/WataLib/Bounding.h"
#include "GameBase/Manager/CollisiionManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
CompositeEntity::CompositeEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	CharacterEntity(resources, scale,position,rotation)
{
}

/// <summary>
/// デストラクタ
/// </summary>
CompositeEntity::~CompositeEntity()
{
}

/// <summary>
/// パーツの追加
/// </summary>
/// <param name="parts">パーツ</param>
void CompositeEntity::AddChild(std::unique_ptr<CompositeEntity> parts)
{

	parts->Initialize();

	m_parts.push_back(std::move(parts));

}

/// <summary>
/// 初期化
/// </summary>
void CompositeEntity::Initialize()
{

	CharacterEntity::Initialize();

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void CompositeEntity::Update(const float& elapsedTime)
{

	CharacterEntity::Update(elapsedTime);

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void CompositeEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	CharacterEntity::Render(view, projection);

}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void CompositeEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	CharacterEntity::OnCollisionEnter(object, tag);

}

/// <summary>
/// アニメーションの登録
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
/// <param name="datas">アニメーションのデータ</param>
/// <param name="partsName">パーツ名</param>
/// <param name="isNormalAnimation">初期アニメーションかどうか</param>
void CompositeEntity::SetAnimationData(const std::string& animationType
	, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
	, const std::string& partsName
	, bool isNormalAnimation)
{

	CharacterEntity::SetAnimationData(animationType, datas, partsName, isNormalAnimation);

}

/// <summary>
/// アニメーションの切り替え
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
void CompositeEntity::ChangeAnimation(const std::string& animationType)
{

	CharacterEntity::ChangeAnimation(animationType);

}
