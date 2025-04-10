#include "pch.h"
#include "BossEnemy.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyBottom.h"

#include "Libraries/WataLib/Json.h"
#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/CollisiionManager.h"
#include "Game/Player/Player.h"
#include "Game/Observer/Messenger.h"
#include "Game/Params.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/RisingPillar/RisingPillarvAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierDefenseAction.h"
#include "Game/Enemys/BossEnemy/Barrier/Barrier.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/RushAttack/BossRushAttackAction.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
BossEnemy::BossEnemy(CommonResources* resources, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation)
	:
	EnemyEntity(resources,scale,position,rotation)
	,m_animationDatas{}
	,m_gravity{}
	, m_hp{}
	,m_behavior{}
	,m_player{}
	,m_attackState{}
	,m_punchTime{}
	,m_isActives{true}
	,m_beam{}
	,m_shadow{}
	,m_action{}
	,m_barrier{}
	,m_velocity{}
	,m_currentAction{}
	,m_isAction{}
{
	m_behavior = std::make_unique<BehaviorTree>();
	m_beam = std::make_unique<Beam>(resources);

	m_shadow = std::make_unique<WataLib::Shadow>();

	m_barrier = std::make_unique<Barrier>(BaseEntity::GetCommonResources(), this);

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemy::~BossEnemy()
{
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
void BossEnemy::AddPointer(Player* player, StageObjectManager* stageObjectManager)
{


	m_player = player;

	m_stageObjectmanger = stageObjectManager;

	m_beam->AddPointer(this,player);
}


/// <summary>
/// 初期化
/// </summary>
void BossEnemy::Initialize()
{

	EnemyEntity::Initialize();

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();



	//「Body」を生成する
	AddChild(std::make_unique<BossEnemyBottom>(BaseEntity::GetCommonResources(),
		this,
		this,
		Params::BOSSENEMY_BODY_SCALE,
		Params::BOSSENEMY_BODY_POSITION,
		Params::BOSSENEMY_BODY_ROTATION));

	//アニメーションデータの読み込み
	std::unique_ptr<WataLib::Json> json = std::make_unique<WataLib::Json>();

	m_animationDatas["Idle"] = json->LoadAnimationData(L"BossEnemy/Idle");
	m_animationDatas["FallDown"] = json->LoadAnimationData(L"BossEnemy/FallDown");
	m_animationDatas["BeamAttack"] = json->LoadAnimationData(L"BossEnemy/BeamAttack");
	m_animationDatas["BeamAttackEnd"] = json->LoadAnimationData(L"BossEnemy/BeamAttackEnd");
	m_animationDatas["Move"] = json->LoadAnimationData(L"BossEnemy/Move");
	m_animationDatas["Punch"] = json->LoadAnimationData(L"BossEnemy/Punch");
	m_animationDatas["Barrier"] = json->LoadAnimationData(L"BossEnemy/Barrier");
	m_animationDatas["BarrierEnd"] = json->LoadAnimationData(L"BossEnemy/BarrierEnd");
	m_animationDatas["JumpCharge"] = json->LoadAnimationData(L"BossEnemy/JumpCharge");
	
	////各パーツにアニメーションを登録
	SetAnimationData("Idle", m_animationDatas,"", true);
	SetAnimationData("FallDown", m_animationDatas);
	SetAnimationData("BeamAttack", m_animationDatas);
	SetAnimationData("BeamAttackEnd", m_animationDatas);
	SetAnimationData("Move", m_animationDatas);
	SetAnimationData("Punch", m_animationDatas);
	SetAnimationData("Barrier", m_animationDatas);
	SetAnimationData("BarrierEnd", m_animationDatas);
	SetAnimationData("JumpCharge", m_animationDatas);

	m_behavior->AddPointer(m_player, this);

	//初期化
	m_behavior->Initialize(BaseEntity::GetCommonResources());
	
	m_beam->Initialize();

	m_barrier->Initialize();

	m_shadow->Initialize(device, context, states);;

	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), Params::BOSSENEMY_SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Params::BOSSENEMY_BOX_COLLIDER_SIZE);

	m_gravity = Params::GRAVITY;

	m_hp = Params::BOSSENEMY_MAX_HP;

	Messenger::Attach(EventParams::EventType::BoomerangGetReadyEnd, this);
	Messenger::Attach(EventParams::EventType::BossBeamAttackEnd, this);

	m_attackState = AttackState::None;

	m_action["Beam"] = std::make_unique<BossBeamAttackAction>(BaseEntity::GetCommonResources(),this,m_beam.get(),m_player);
	m_action["Beam"]->Initialize();

	m_action["RisingPillar"] = std::make_unique<RisingPillarvAction>(BaseEntity::GetCommonResources(), this,  m_player,m_stageObjectmanger);
	m_action["RisingPillar"]->Initialize();


	m_action["BarrierDefense"] = std::make_unique<BarrierDefenseAction>(BaseEntity::GetCommonResources(), this,m_barrier.get());
	m_action["BarrierDefense"]->Initialize();

	m_action["JumpAttack"] = std::make_unique<BossJumpAttackAction>(BaseEntity::GetCommonResources(), this, m_player);
	m_action["JumpAttack"]->Initialize();

	m_action["RushAttack"] = std::make_unique<BossRushAttackAction>(BaseEntity::GetCommonResources(), this, m_player);
	m_action["RushAttack"]->Initialize();

	m_target = m_player;


}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BossEnemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//オブジェクトか描画が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}


	EnemyEntity::Render(view, projection);

	CollisionEntity::GetBounding()->DrawBoundingSphere(BaseEntity::GetPosition(), view, projection);
	CollisionEntity::GetBounding()->DrawBoundingBox(BaseEntity::GetPosition(), view, projection);

	//パーツの描画
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Render(view,projection);
	}

	if (m_hp > 0)
	{
		m_beam->Render(view, projection);
		m_barrier->Render(view, projection);

	}



	DirectX::SimpleMath::Vector3 shadowPos = BaseEntity::GetPosition();
	shadowPos.y = 0.1f;

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();



	// 自機の影を描画する
	m_shadow->Render(context, states, view, projection, shadowPos, 3.5f);

}


/// <summary>
/// 当たり判定クラスへ追加
/// </summary>
void BossEnemy::AddCollision(CollisionManager* collsionManager)
{
	//コリジョンマネージャーに追加
	collsionManager->AddCollsion(this);

	for (auto& part : CompositeEntity::GetParts())
	{
		part->AddCollision(collsionManager);
	}

	m_beam->AddCollionManager(collsionManager);

	m_barrier->AddCollision(collsionManager);

}
/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void BossEnemy::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	switch (tag)
	{
		case CollisionEntity::CollisionTag::None:
			break;
		case CollisionEntity::CollisionTag::Player:
			break;
		case CollisionEntity::CollisionTag::PlayerParts:
			break;
		case CollisionEntity::CollisionTag::Stage:
			m_velocity.y = 0.0f;

			if (m_currentAction.first == "JumpAttack")
			{
				m_isAction = true;
				{
				}
			}

			break;
		case CollisionEntity::CollisionTag::Enemy:
			break;
		case CollisionEntity::CollisionTag::EnemyParts:
			break;
		case CollisionEntity::CollisionTag::Boomerang:
			break;
		case CollisionEntity::CollisionTag::Beam:
			break;
		case CollisionEntity::CollisionTag::Barrier:
			break;
		default:
			break;
	}

}



/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BossEnemy::Update(const float& elapsedTime)
{


	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	if (m_hp > 0)
	{
		//ビヘイビアツリーの更新
		m_behavior->Update(elapsedTime);
		m_beam->Update(elapsedTime);
		m_barrier->Update(elapsedTime);
	}

	m_velocity.y -= m_gravity * elapsedTime ;
	

	Vector3 pos = BaseEntity::GetPosition();
	
	pos += m_velocity;

	BaseEntity::SetPosition(pos);
	
	CollisionEntity::GetBounding()->Update(BaseEntity::GetPosition());

	//パーツの更新
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
void BossEnemy::SetAnimationData(std::string animationType, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas, const std::string& partsName, bool isNormalAnimation)
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
void BossEnemy::ChangeAnimation(std::string animationType)
{
	CharacterEntity::ChangeAnimation(animationType);
	//パーツのアニメーションを変更
	for (auto& part : CompositeEntity::GetParts())
	{
		part->ChangeAnimation(animationType);
	}

}



/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">種類</param>
/// <param name="datas">データ</param>
void BossEnemy::Notify(EventParams::EventType type, void* datas)
{
	switch (type)
	{
		case EventParams::EventType::BossBeamAttackEnd:
			m_attackState = AttackState::End;
			break;
		default:
			break;
	}
}

/// <summary>
/// ビーム攻撃
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State BossEnemy::BeamAttack(const float& elapsedTime)
{

	return JumpAttack(elapsedTime);

 
	return Pounding(elapsedTime);

	return m_action["Beam"]->Update(elapsedTime);

	//床と壁の色を変える　太陽を追加して影をつける

}

/// <summary>
/// 歩き
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State BossEnemy::Walk(const float& elapsedTime)
{

	if (CharacterEntity::GetCurrentAnimationType() != "Move")
	{
		ChangeAnimation("Move");
		return IBehaviorNode::State::Runngin;
	}

	//プレイヤの座標の取得
	Vector3 playerPosition = m_player->GetPosition();

	//方向を求める
	Vector3 direction = playerPosition - BaseEntity::GetPosition();
	//正規化
	direction.Normalize();

	direction *= Params::BOSSENEMY_MOVE_SPEED * elapsedTime;

	BaseEntity::SetPosition( BaseEntity::GetPosition() + direction);


	return IBehaviorNode::State::Success;
}

/// <summary>
/// パンチ攻撃
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State BossEnemy::Pounding(const float& elapsedTime)
{

	if (CharacterEntity::GetCurrentAnimationType() != "Punch")
	{
		ChangeAnimation("Punch");
		m_punchTime = 0;

		return IBehaviorNode::State::Runngin;
	}



	if (m_punchTime >= PUNCHTIME)
	{
		ChangeAnimation("Idel");

		return IBehaviorNode::State::Success;
	}

	m_punchTime += elapsedTime;
	return IBehaviorNode::State::Runngin;
}

/// <summary>
/// プレイヤの方向を向く
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State BossEnemy::FacingThePlayer(float elapsdTime)
{

	//向きたい方向
	DirectX::SimpleMath::Vector3 direction = m_player->GetPosition() - BaseEntity::GetPosition();
	direction.Normalize();
	//今の敵の前方向
	DirectX::SimpleMath::Vector3 forward = Vector3::Transform(Vector3::Backward, BaseEntity::GetRotation());
	//forward.Normalize();
	//回転軸の作成
	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		//正なら上方向
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		//負なら下方向
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//角度を求める
	float moveAngle = forward.Dot(direction);

	//ラジアン値に変換
	moveAngle = acosf(moveAngle);

	//角度と速度の比較で小さいほうを取得
	moveAngle = std::min(moveAngle, Params::BOSSENEMY_ROTATION_SPEED * elapsdTime);

	//敵の回転の取得
	DirectX::SimpleMath::Quaternion Rotate = BaseEntity::GetRotation();
	//Y軸に対して回転をかける
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	BaseEntity::SetRotation(Rotate);

	return IBehaviorNode::State::Success;

}

IBehaviorNode::State BossEnemy::BarrierDefense(float elapsdTime)
{
	return m_action["BarrierDefense"]->Update(elapsdTime);
}

IBehaviorNode::State BossEnemy::JumpAttack(float elapsdTime)
{

	if (m_currentAction.first != "JumpAttack")
	{
		ChangeAction("JumpAttack");
	}


	if (m_isAction)
	{

		m_isAction = false;
		m_velocity = Vector3::Zero;
		InitalizeAction();
		return IBehaviorNode::State::Success;

	}


	return m_action["JumpAttack"]->Update(elapsdTime);
}

void BossEnemy::ChangeAction(std::string typeName)
{
	if (m_currentAction.second != nullptr)
	{
		m_currentAction.second->Exit();

	}

	m_currentAction.second = m_action[typeName].get();
	m_currentAction.second->Enter();

	m_currentAction.first = typeName;



}

void BossEnemy::InitalizeAction()
{
	m_currentAction.first = "";
	m_isAction = false;
}


