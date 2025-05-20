#include "pch.h"
#include "BossEnemyPartsBase.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"

#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Animation.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Params.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="root">ボス敵の根のクラス</param>
/// <param name="parent">親</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="partsName">パーツ名</param>
/// <param name="partsHP">パーツのＨＰ</param>
/// <param name="boxColliderSize">ボックスの当たり判定の大きさ</param>
/// <param name="SphereColliderSize">スフィアの当たり判定の大きさ</param>
BossEnemyPartsBase::BossEnemyPartsBase(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation, std::string partsName, int partsHP
	, DirectX::SimpleMath::Vector3 boxColliderSize, float SphereColliderSize)
	:
	CompositeEntity(resources,scale,position,rotation),
	m_model{}
	,m_root{root}
	,m_initialScale{scale}
	,m_initialPosition{position}
	,m_initialRotation{rotation}
	,m_partsName{partsName}
	,m_partsHP{partsHP}
	,m_boxColliderSize{boxColliderSize}
	,m_sphereColliderSize{SphereColliderSize}
{
	BaseEntity::SetParent(parent);
}

/// <summary>
/// 初期化
/// </summary>
void BossEnemyPartsBase::Initialize()
{
	CompositeEntity::Initialize();

	//大きさの設定
	BaseEntity::SetScale(m_initialScale);
	//親の回転を取得
	BaseEntity::SetRotation(m_initialRotation * CharacterEntity::GetAnimation()->GetRotation());
	//座標の計算
	BaseEntity::SetPosition(m_initialPosition + CharacterEntity::GetAnimation()->GetPosition());

	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), m_sphereColliderSize * BaseEntity::GetScale().x);
	CollisionEntity::GetBounding()->CreateBoundingOrientedBox(BaseEntity::GetPosition(), BaseEntity::GetRotation(), m_boxColliderSize * BaseEntity::GetScale());


}



/// <summary>
/// デストラクタ
/// </summary>
BossEnemyPartsBase::~BossEnemyPartsBase()
{
	
}


/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BossEnemyPartsBase::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//オブジェクトか描画が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}

	CompositeEntity::Render(view, projection);

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	// モデルのエフェクトを更新する
	m_model->UpdateEffects([&](DirectX::IEffect* effect)
		{
			// ベイシックエフェクトを取得する
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);


			// ディフューズカラーを設定する
			basicEffect->SetDiffuseColor(DirectX::Colors::LightSlateGray);
			// スペキュラカラーを設定する
			basicEffect->SetSpecularColor(DirectX::Colors::LightSlateGray);

			

			// スペキュラパワーを設定する
			basicEffect->SetSpecularPower(20.0f);
		});

	//モデルの描画
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection);




	CollisionEntity::GetBounding()->DrawBoundingSphere(BaseEntity::GetPosition(), view, projection);
	CollisionEntity::GetBounding()->DrawBoundingOrientedBox(BaseEntity::GetPosition(), BaseEntity::GetRotation(), view, projection);

	//パーツの描画
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Render(view, projection);
	}

	

}

/// <summary>
/// 当たり判定クラスに追加
/// </summary>
/// <param name="collsionManager">当たり判定クラス</param>
void BossEnemyPartsBase::AddCollision(CollisionManager* collsionManager)
{

	CollisionEntity::AddCollision(collsionManager);

	for (auto& part : CompositeEntity::GetParts())
	{
		part->AddCollision(collsionManager);
	}
}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void BossEnemyPartsBase::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	switch (tag)
	{
		case CollisionEntity::CollisionTag::BOOMERANG:
			m_partsHP -= Params::BOOMERANG_DAMAGE;
			m_partsHP = std::max(m_partsHP, 0);
			m_root->Damage(Params::BOOMERANG_DAMAGE);

			////部位破壊
			//if (m_partsHP <= 0)
			//{
			//	//座標を決める
			//	m_root->Damage(Params::BOOMERANG_DAMAGE * 2);

			//	//取り出しよう変数
			//	Vector3 position;
			//	Vector3 scale;
			//	Quaternion rotation;
			//	//行列から求める
			//	Matrix matrix = BaseEntity::GetWorldMatrix();
			//	matrix.Decompose(scale, rotation, position);

			//	UnknownDataTwo aa = { static_cast<void*>(&position) ,static_cast<void*>(&scale)};
			//	Messe
			// nger::GetInstance()->Notify(GameMessageType::CreateExplosion, &aa);
			//}
			

			{
				{
					Vector3 pos = object->GetPosition();
					Vector3 scale = BaseEntity::GetScale();

					UnknownDataThree aa = { static_cast<void*>(&pos) ,static_cast<void*>(&scale) };

					Messenger::GetInstance()->Notify(GameMessageType::CREATE_HIT_EFFECT, &aa);
				}

			}


			break;
		default:
			break;
	}


}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BossEnemyPartsBase::Update(const float& elapsedTime)
{
	
	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}



	CompositeEntity::Update(elapsedTime);

	//親があれば
	if (BaseEntity::GetIsParent())
	{
		//親の回転を取得
		BaseEntity::SetLocalRotation(m_initialRotation * CharacterEntity::GetAnimation()->GetRotation());
		//座標の計算
		BaseEntity::SetLocalPosition(m_initialPosition + CharacterEntity::GetAnimation()->GetPosition());

	}


	//パーツの更新
	for (auto& parts : CompositeEntity::GetParts())
	{
		parts->Update(elapsedTime);
	}


}

/// <summary>
/// アニメーションの登録
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
/// <param name="datas">アニメーションのデータ</param>
/// <param name="partsName">パーツ名</param>
/// <param name="isNormalAnimation">初期アニメーションかどうか</param>
void BossEnemyPartsBase::SetAnimationData(std::string animationType, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas, const std::string& partsName, bool isNormalAnimation)
{
		UNREFERENCED_PARAMETER(partsName);


	//アニメーションの登録
	CharacterEntity::GetAnimation()->SetAnimationData(animationType, datas[animationType][m_partsName], isNormalAnimation);

	//子のアニメーションの登録
	for (auto& part : CompositeEntity::GetParts())
	{
		part->SetAnimationData(animationType, datas, m_partsName, isNormalAnimation);
	}


}

/// <summary>
/// アニメーションの切り替え
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
void BossEnemyPartsBase::ChangeAnimation(std::string animationType)
{

	//アニメーションの変更
	CharacterEntity::GetAnimation()->ChangeAnimation(animationType);

	//子のアニメーションの変更
	for (auto& part : CompositeEntity::GetParts())
	{
		part->ChangeAnimation(animationType);
	}

}


