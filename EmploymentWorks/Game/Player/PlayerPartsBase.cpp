#include "pch.h"
#include "PlayerPartsBase.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"

#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/MyLib/DebugString.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="parent">親</param>
/// <param name="partsName">パーツ名</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
PlayerPartsBase::PlayerPartsBase(CommonResources* resources,
	CharacterEntity* parent
	, std::string partsName
	, DirectX::SimpleMath::Vector3 scale
	, DirectX::SimpleMath::Vector3 position
	, DirectX::SimpleMath::Quaternion rotation)
	:
	m_parent{parent}
	,m_partsName{partsName}
	,m_initialScale{scale}
	,m_initialPosition{position}
	,m_initialRotation{rotation}
	,m_isParentActive{true}
	,CompositeEntity(resources, scale,position,rotation)
{
	BaseEntity::SetParent(parent);
}


/// <summary>
/// デストラクタ
/// </summary>
PlayerPartsBase::~PlayerPartsBase()
{
}

/// <summary>
/// 初期化
/// </summary>
void PlayerPartsBase::Initialize()
{
	BaseEntity::Initialize();
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void PlayerPartsBase::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{


	//オブジェクトか描画が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	BaseEntity::Render(view, projection);

	//モデルの描画
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection);

	//パーツの描画
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Render(view,projection);
	}

	auto debug = BaseEntity::GetCommonResources()->GetDebugString();

	//debug->AddString("Pos : %f, %f", BaseEntity::GetRotation().x, BaseEntity::GetRotation().y);

}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void PlayerPartsBase::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{



}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerPartsBase::Update(const float& elapsedTime)
{

	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}


	CompositeEntity::Update(elapsedTime);

	//座標の計算
	BaseEntity::SetLocalPosition(m_initialPosition + CharacterEntity::GetAnimation()->GetPosition());
	//親の回転を取得
	BaseEntity::SetLocalRotation(m_initialRotation * CharacterEntity::GetAnimation()->GetRotation());

	//パーツの描画
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Update(elapsedTime);
	}

}

/// <summary>
/// アニメーションの登録
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
/// <param name="datas">アニメーションのデータ</param>
/// <param name="partsName">パーツ名</param>
/// <param name="isNormalAnimation">初期アニメーションかどうか</param>
void PlayerPartsBase::SetAnimationData(std::string animationType
	, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
	, const std::string& partsName
	, bool isNormalAnimation)
{
	//アニメーションの登録
	CharacterEntity::GetAnimation()->SetAnimationData(animationType, datas[animationType][m_partsName], isNormalAnimation);

	//子のアニメーションの登録
	for (auto& part : CompositeEntity::GetParts())
	{
		part->SetAnimationData(animationType, datas,m_partsName ,isNormalAnimation);
	}
	

}

/// <summary>
/// アニメーションの切り替え
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
void PlayerPartsBase::ChangeAnimation(std::string animationType)
{

	//アニメーションの変更
	CharacterEntity::GetAnimation()->ChangeAnimation(animationType);

	//子のアニメーションの変更
	for (auto& part : CompositeEntity::GetParts())
	{
		part->ChangeAnimation(animationType);
	}
}

