#include "pch.h"
#include "CharacterEntity.h"
#include "Libraries/WataLib/Bounding.h"
#include "GameBase/Manager/CollisiionManager.h"
#include "Libraries/WataLib/Animation.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
CharacterEntity::CharacterEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	MoveEntity(resources, scale,position,rotation)
{

	m_animation = std::make_unique<WataLib::Animation>();

}

/// <summary>
/// デストラクタ
/// </summary>
CharacterEntity::~CharacterEntity()
{
}

/// <summary>
/// アニメーションの登録
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
/// <param name="datas">アニメーションのデータ</param>
/// <param name="partsName">パーツ名</param>
/// <param name="isNormalAnimation">初期アニメーションかどうか</param>
void CharacterEntity::SetAnimationData(const std::string& animationType
	, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
	, const std::string& partsName
	, bool isNormalAnimation)
{
	//アニメーションの登録
	m_animation->SetAnimationData(animationType, datas[animationType][partsName], isNormalAnimation);

	//初期状態なら
	if (isNormalAnimation)
	{
		//名前の変更
		m_currentAnimationType = animationType;
	}


}

/// <summary>
/// アニメーションの切り替え
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
void CharacterEntity::ChangeAnimation(const std::string& animationType)
{
	//名前の変更
	m_currentAnimationType = animationType;

	m_animation->ChangeAnimation(m_currentAnimationType);

}

/// <summary>
/// 初期化
/// </summary>
void CharacterEntity::Initialize()
{

	MoveEntity::Initialize();

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void CharacterEntity::Update(const float& elapsedTime)
{
	//アニメーションがあれば
	if (m_animation)
	{
		//アニメーションの更新
		m_animation->Update(elapsedTime);

	}


	MoveEntity::Update(elapsedTime);


}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void CharacterEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	MoveEntity::Render(view, projection);

}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void CharacterEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	MoveEntity::OnCollisionEnter(object, tag);

}
