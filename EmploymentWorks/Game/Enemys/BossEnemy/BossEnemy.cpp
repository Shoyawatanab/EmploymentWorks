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
#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierDefenseAction.h"
#include "Game/Enemys/BossEnemy/Barrier/Barrier.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/RushAttack/BossRushAttackAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/Walking/WalkingActionComtroller.h"
#include "Game/Enemys/BossEnemy/ActionNode/SwingDownAttack/SwingDownAttackAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/Idleing/IdleingActionComtroller.h"

#include "Game/Observer/Enemy/EnemyMessenger.h"
#include "Libraries/MyLib/DebugString.h"
#include "Game/InstanceRegistry.h"



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
	,m_punchTime{}
	,m_beam{}
	,m_shadow{}
	,m_barrier{}
	,m_isAction{}
	,m_action{}
	,m_isGrounded{false}
	,m_actionList{}
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

	m_actionList.clear();
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
void BossEnemy::AddPointer( StageObjectManager* stageObjectManager)
{


	m_stageObjectmanger = stageObjectManager;

}

/// <summary>
/// 行動の切り替え
/// </summary>
/// <param name="actionName">行動の名前</param>
void BossEnemy::ChangeAction(const std::string actionName)
{
	//リストから佐賀図
	auto it = m_actionList.find(actionName);

	//あれば
	if (it != m_actionList.end())
	{
		//切り替え前の行動があるかどうか
		if (m_action.second != nullptr)
		{
			//状態を抜けるときの処理
			m_action.second->Exit();
		}
		//実行行動の名前の切り替え
		m_action.first = actionName;
		//実行行動の切り替え
		m_action.second = it->second.get();
		//状態に入った時の処理
		m_action.second->Enter();
		

	}


}


/// <summary>
/// 初期化
/// </summary>
void BossEnemy::Initialize()
{

	EnemyEntity::Initialize();

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

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
	m_animationDatas["SwingDown"] = json->LoadAnimationData(L"BossEnemy/SwingDown");
	m_animationDatas["Barrier"] = json->LoadAnimationData(L"BossEnemy/Barrier");
	m_animationDatas["BarrierEnd"] = json->LoadAnimationData(L"BossEnemy/BarrierEnd");
	m_animationDatas["JumpCharge"] = json->LoadAnimationData(L"BossEnemy/JumpCharge");
	
	////各パーツにアニメーションを登録
	SetAnimationData("Idle", m_animationDatas,"", true);
	SetAnimationData("FallDown", m_animationDatas);
	SetAnimationData("BeamAttack", m_animationDatas);
	SetAnimationData("BeamAttackEnd", m_animationDatas);
	SetAnimationData("Move", m_animationDatas);
	SetAnimationData("SwingDown", m_animationDatas);
	SetAnimationData("Barrier", m_animationDatas);
	SetAnimationData("BarrierEnd", m_animationDatas);
	SetAnimationData("JumpCharge", m_animationDatas);


	//各アクションの作成
	m_actionList["Idle"] = std::make_unique<IdleingActionComtroller>(BaseEntity::GetCommonResources(), this);
	m_actionList["JumpAttack"] = std::make_unique<BossJumpAttackAction>(BaseEntity::GetCommonResources(),this,m_player);
	m_actionList["RushAttack"] = std::make_unique<BossRushAttackAction>(BaseEntity::GetCommonResources(),this,m_player);
	m_actionList["BarrierDefense"] = std::make_unique<BarrierDefenseAction>(BaseEntity::GetCommonResources(), this,m_barrier.get());
	m_actionList["BeamAttack"] = std::make_unique<BossBeamAttackAction>(BaseEntity::GetCommonResources(), this, m_beam.get(),m_player);
	m_actionList["Walking"] = std::make_unique<WalkingActionComtroller>(BaseEntity::GetCommonResources(), this,m_player);
	m_actionList["SwingDown"] = std::make_unique<SwingDownAttackAction>(BaseEntity::GetCommonResources(), this);

	//初期状態
	ChangeAction("Idle");

	//初期化
	m_behavior->Initialize(BaseEntity::GetCommonResources(),this);
	m_beam->Initialize();
	m_barrier->Initialize();
	m_shadow->Initialize(device, context, states);

	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), Params::BOSSENEMY_SPHERE_COLLIDER_SIZE * BaseEntity::GetScale().x);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Params::BOSSENEMY_BOX_COLLIDER_SIZE * BaseEntity::GetScale());

	m_gravity = Params::GRAVITY;

	m_hp = Params::BOSSENEMY_MAX_HP;

	Messenger::GetInstance()->Rigister(GameMessageType::BOSS_BEAM_ATTACK_END, this);

	//
	EnemyMessenger::GetInstance()->Rigister(GetID(), this);


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

	//当たり判定の描画
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
	shadowPos.y = Params::SHADOW_POSITION_Y;

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	// 自機の影を描画する
	m_shadow->Render(context, states, view, projection, shadowPos, Params::BOSSENEMY_SHADOW_RADIUS * BaseEntity::GetScale().x);
	

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

	UNREFERENCED_PARAMETER(tag);
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::STAGE:
			m_isGrounded = true;
			break;
		default:
			break;
	}

}

/// <summary>
/// 当たり続けているときに呼ばれる関数
/// </summary>
/// <param name="object"></param>
/// <param name="tag"></param>
void BossEnemy::OnCollisionStay(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::STAGE:
		{
			Vector3 velocity = BaseEntity::GetVelocity();

			velocity.y = 0.0f;

			BaseEntity::SetVelocity(velocity);
		}
		break;
		default:
			break;
	}



}

/// <summary>
/// 離れた時に呼ばれる関数
/// </summary>
/// <param name="object"></param>
/// <param name="tag"></param>
void BossEnemy::OnCollisionExit(CollisionEntity* object, CollisionTag tag)
{

	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::STAGE:
			m_isGrounded = false;
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
		m_beam->Update(elapsedTime);
		m_barrier->Update(elapsedTime);
	}



	//行動の更新
	//if (m_action.second->Update(elapsedTime) == IAction::ActionState::END)
	//{
	//	//ビヘイビアツリーの更新
	//	m_behavior->Update(elapsedTime);

	// }	

	CollisionEntity::Update(elapsedTime);
	
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
/// 通知を受け取る関数（Game）
/// </summary>
/// <param name="type">種類</param>
/// <param name="datas">データ</param>
void BossEnemy::Notify(const Telegram<GameMessageType>& telegram)
{
	
	switch (telegram.messageType)
	{
		case GameMessageType::BOSS_BEAM_ATTACK_END:
			break;
		default:
			break;
	}

}

/// <summary>
/// 通知を受け取る関数（Enemy）
/// </summary>
/// <param name="telegram"></param>
void BossEnemy::Notify(const Telegram<EnemyMessageType>& telegram)
{


	switch (telegram.messageType)
	{
		case EnemyMessageType::BARRIER_DEFENSE:
			ChangeAction("BarrierDefense");
			break;
		case EnemyMessageType::BEAM_ATTACK:
			ChangeAction("BeamAttack");
			break;
		case EnemyMessageType::JUMP_ATTACK:
			ChangeAction("JumpAttack");

			break;
		case EnemyMessageType::SWING_DOWN:
			ChangeAction("SwingDown");
			break;
		case EnemyMessageType::WALKING:
			ChangeAction("Walking");
			break;
		default:
			break;
	}




}



