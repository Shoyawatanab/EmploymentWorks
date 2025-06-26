#include "pch.h"
#include "BirdEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/Model/BirdEnemyModel.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Params.h"


/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="player">プレイヤ</param>
BirdEnemy::BirdEnemy(Scene* scene, DirectX::SimpleMath::Vector3 scale
	, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation, Player* player)
	:
	EnemyBase(scene,10)
	,m_target{player}
	,m_bullets{}
{

	using namespace DirectX::SimpleMath;

	//当たり判定の作成
	AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
		, Vector3(0.8f,0.8f,0.8f) * scale
		, 2.0f * std::max({ scale.x, scale.y, scale.z }));


	//モデルの作成
	auto model = GetScene()->AddActor<BirdEnemyModel>(GetScene());
	//親子関係をセット
	model->GetTransform()->SetParent(GetTransform());

	SetModel(model);

	for (int i = 0; i < 5; i++)
	{
		auto bullet = GetScene()->AddActor<BirdEnemyBullet>(GetScene(), this);
		m_bullets.push_back(bullet);
	}

	//初期状態の適用 Jsonで管理
	GetTransform()->SetScale(scale);
	GetTransform()->Translate(position);
	GetTransform()->SetRotate(rotation);

	m_stateMachine = std::make_unique<BirdEnemyStateMachine>(this);


}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemy::~BirdEnemy()
{
}

/// <summary>
/// 個別アップデート
/// </summary>
/// <param name="deltaTime"></param>
void BirdEnemy::UpdateActor(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (FadeManager::GetInstance()->GetIsFade())
	{
		return;
	}

	//m_stateMachine->Update(deltaTime);

	//常にターゲットに向くように
	//Rotate(deltaTime);

}

/// <summary>
/// 
/// </summary>
/// <param name="collider"></param>
void BirdEnemy::OnCollisionEnter(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::BOOMERANG:
		{
			int damage = Params::BOOMERANG_DAMAGE;

			HpDecrease(damage);
			SceneMessenger::GetInstance()->Notify(SceneMessageType::ENEMY_DAMAGE, &damage);


			float ratio = GetHpRatio();
			SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_DAMAGE, &ratio);

		}

		//Hpが０になれば
		if (GetHp() <= 0)
		{


			
		}

		break;

		default:
			break;
	}

}

//修正に強い　疎結合ー＞どうやって





/// <summary>
/// ターゲットに対して回転
/// </summary>
/// <param name="deltaTime"></param>
void BirdEnemy::Rotate(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(deltaTime);

	//敵の現在の座標の取得
	Vector3 enemyPosition = GetTransform()->GetWorldPosition();
	//プレイヤの現在の座標の取得
	Vector3 playerPosition = m_target->GetTransform()->GetWorldPosition();
	//敵からプレイヤの方向ベクトルの計算
	Vector3 toPlayer = playerPosition - enemyPosition;
	//yawの計算　（左右回転）
	//xz平面で敵からプレイヤの方向を求める
	float yaw = atan2(toPlayer.x, toPlayer.z);
	//pitchの計算（上下回転）
	//敵からプレイヤのウ違勅方向を求める
	float pitch = atan2(toPlayer.y, sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z));

	//yaw pitchから回転を計算 pitchは反転させる
	GetTransform()->SetRotate(Quaternion::CreateFromYawPitchRoll(yaw, -pitch, 0.0f));



}



/// <summary>
/// 非アクティブの弾の取得
/// </summary>
BirdEnemyBullet* BirdEnemy::GetInactiveBullet()
{

	for (auto& bullet : m_bullets)
	{
		if (!bullet->GetActive())
		{
			return bullet;
		}
	}


	return nullptr;

}





