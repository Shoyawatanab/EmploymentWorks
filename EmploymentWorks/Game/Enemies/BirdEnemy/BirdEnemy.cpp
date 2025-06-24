#include "pch.h"
#include "BirdEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/Model/BirdEnemyModel.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="player">プレイヤ</param>
BirdEnemy::BirdEnemy(Scene* scene, Player* player)
	:
	EnemyBase(scene,10)
	,m_target{player}
	,m_bullets{}
{
	using namespace DirectX::SimpleMath;


	//モデルの作成
	auto model = GetScene()->AddActor<BirdEnemyModel>(GetScene());
	//モデルの大きさをプレイヤの設定に
	model->GetTransform()->SetScale(Vector3(0.5f,0.5f,0.5f));
	model->GetTransform()->Translate(Vector3::Zero);
	model->GetTransform()->SetRotate(Quaternion::Identity);
	//親子関係をセット
	model->GetTransform()->SetParent(GetTransform());

	SetModel(model);

	for (int i = 0; i < 1; i++)
	{
		auto bullet = GetScene()->AddActor<BirdEnemyBullet>(GetScene(), this);
		m_bullets.push_back(bullet);
	}

	//初期状態の適用 Jsonで管理
	GetTransform()->SetScale(Vector3::One);
	GetTransform()->Translate(Vector3(0,3,0));
	GetTransform()->SetRotate(Quaternion::Identity);

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
	m_stateMachine->Update(deltaTime);

	//常にターゲットに向くように
	Rotate(deltaTime);

}

/// <summary>
/// 
/// </summary>
/// <param name="collider"></param>
void BirdEnemy::OnCollisionEnter(ColliderComponent* collider)
{

}

/// <summary>
/// 
/// </summary>
/// <param name="collider"></param>
void BirdEnemy::OnCollisionStay(ColliderComponent* collider)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="collider"></param>
void BirdEnemy::OnCollisionExit(ColliderComponent* collider)
{
}

/// <summary>
/// ターゲットに対して回転
/// </summary>
/// <param name="deltaTime"></param>
void BirdEnemy::Rotate(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

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
