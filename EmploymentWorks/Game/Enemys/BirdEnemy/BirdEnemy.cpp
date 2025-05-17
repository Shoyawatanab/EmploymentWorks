#include "pch.h"
#include "BirdEnemy.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Json.h"
#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"
#include "Game/Player/Player.h"
#include "Game/Observer/Messenger.h"
#include "Game/Enemys/BirdEnemy/BirdEnemyBody.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラク
/// </summary>
BirdEnemy::BirdEnemy(CommonResources* resources
	, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation)
	:
	EnemyEntity(resources,scale,position,rotation)
	,m_hp{}
	, m_enemyManager{}
	, m_player{}
	,m_shadow{}
	, m_punchTime{}
	,m_beam{}
	,m_stateMachine{}
	,m_beamPosition{}

{

	m_stateMachine = std::make_unique<BirdEnemyStateMachine>();

	m_shadow = std::make_unique<WataLib::Shadow>();
}


/// <summary>
/// デストラクタ
/// </summary>
BirdEnemy::~BirdEnemy()
{
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
void BirdEnemy::AddPointer(Player* player)
{
	m_player = player;

	m_stateMachine->AddPointer(m_player, this);

}

/// <summary>
/// 回転
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemy::Rotate(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	//敵の現在の座標の取得
	Vector3 enemyPosition = BaseEntity::GetPosition();
	//プレイヤの現在の座標の取得
	Vector3 playerPosition = m_player->GetPosition();
	//敵からプレイヤの方向ベクトルの計算
	Vector3 toPlayer = playerPosition - enemyPosition;
	//yawの計算　（左右回転）
	//xz平面で敵からプレイヤの方向を求める
	float yaw = atan2(toPlayer.x, toPlayer.z);
	//pitchの計算（上下回転）
	//敵からプレイヤのウ違勅方向を求める
	float pitch = atan2(toPlayer.y, sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z));

	//yaw pitchから回転を計算 pitchは反転させる
	BaseEntity::SetRotation(Quaternion::CreateFromYawPitchRoll(yaw, -pitch, 0.0f));

	Vector3 pos = Vector3::Transform(Params::BIRDENEMY_BEAM_SHOT_POSITION, BaseEntity::GetRotation());

	m_beamPosition = BaseEntity::GetPosition() + pos;;




}


/// <summary>
/// 初期化
/// </summary>
void BirdEnemy::Initialize()
{

	EnemyEntity::Initialize();

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();





	m_stateMachine->Initialize(BaseEntity::GetCommonResources(), m_stateMachine->GetBirdEnemyldling());

	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), Params::BIRDENEMY_SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Params::BIRDENEMY_BOX_COLLIDER_SIZE);

	//10作っておく
	for (int i = 0; i < 10; i++)
	{
		auto beam = std::make_unique<BirdEnemyBeam>(BaseEntity::GetCommonResources(),m_player,this);
		beam->Initialize();

		m_beam.push_back(std::move(beam));
	}

	m_hp = Params::BIRDENEMY_HP;

	AddChild(std::make_unique<BirdEnemyBody>(BaseEntity::GetCommonResources(),
		this,
		Params::BIRDENEMY_BODY_SCALE,
		Params::BIRDENEMY_BODY_POSITION,
		Params::BIRDENEMY_BODY_ROTATION));

	m_shadow->Initialize(device, context, states);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//オブジェクトか描画が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}

   	EnemyEntity::Render(view, projection);

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

 	if (m_hp <= 0)
	{
		return;
	}




	for (auto& parts : CompositeEntity::GetParts())
	{
		parts->Render(view, projection);
	}


	for (auto& beam : m_beam)
	{
		//idling状態じゃないものを描画する
		if (beam->GetStateMahine()->GetCurrentState() != beam->GetStateMahine()->GetBirdEnemyBeamIdle())
		{

			beam->Render(view, projection);

		}
	}


	DirectX::SimpleMath::Vector3 shadowPos = BaseEntity::GetPosition();
	shadowPos.y = Params::SHADOW_POSITION_Y;




	// 自機の影を描画する
	m_shadow->Render(context, states, view, projection, shadowPos, Params::BIRDENEMY_SHADOW_RADIUS);


}



/// <summary>
/// 当たり判定に追加
/// </summary>
/// <param name="collsionManager">当たり判定クラス</param>
void BirdEnemy::AddCollision(CollisionManager* collsionManager)
{
	//コリジョンマネージャーに追加
	collsionManager->AddCollsion(this);

	for (auto& beam : m_beam)
	{
		beam->AddCollision(collsionManager);
	}

}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手オブジェクト</param>
/// <param name="tag">相手のタグ</param>
void BirdEnemy::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
	switch (tag)
	{
		case CollisionEntity::CollisionTag::Boomerang:

			m_hp -= Params::BOOMERANG_DAMAGE;


			if (m_hp <= 0)
			{
				if (BaseEntity::GetIsEntityActive())
				{

					EnemyEntity::GetEnemyManager()->DeleteRemainingEnemy(this);
					Vector3 scale = BaseEntity::GetScale();
					Vector3 position = object->GetPosition();
					UnknownDataTwo aa = { static_cast<void*>(&position) ,static_cast<void*>(&scale)};
					Messenger::GetInstance()->Notify(GameMessageType::CreateExplosion, &aa);
					BaseEntity::SetIsEntityActive(false);

				}
			}
			else
			{

				Vector3 pos = object->GetPosition();
				Vector3 scale = BaseEntity::GetScale();

				UnknownDataThree aa = { static_cast<void*>(&pos) ,static_cast<void*>(&scale)};

				Messenger::GetInstance()->Notify(GameMessageType::CreateHitEffect, &aa);

			}

			break;
		default:
			break;
	}

}



/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemy::Update(const float& elapsedTime)
{

	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	m_stateMachine->Update(elapsedTime);

	CollisionEntity::GetBounding()->Update(BaseEntity::GetPosition());

   	for (auto& parts : CompositeEntity::GetParts())
	{
		parts->Update(elapsedTime);
	}


	//ビームの更新
	for (auto& beam : m_beam)
	{
		beam->Update(elapsedTime);
	}

}

/// <summary>
/// アニメーションの登録
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
/// <param name="datas">アニメーションデータ</param>
/// <param name="partsName">パーツ名</param>
/// <param name="isNormalAnimation">初期アニメーションかどうか</param>
void BirdEnemy::SetAnimationData(std::string animationType, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas, const std::string& partsName, bool isNormalAnimation)
{
	CharacterEntity::SetAnimationData(animationType, datas, partsName, isNormalAnimation);

	//パーツにアニメーションを登録
	for (auto& part : CompositeEntity::GetParts())
	{
		part->SetAnimationData(animationType, datas, partsName, isNormalAnimation);
	}

}

/// <summary>
/// アニメーションの変更
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
void BirdEnemy::ChangeAnimation(std::string animationType)
{
	CharacterEntity::ChangeAnimation(animationType);
	//パーツのアニメーションを変更
	for (auto& part : CompositeEntity::GetParts())
	{
		part->ChangeAnimation(animationType);
	}
}






