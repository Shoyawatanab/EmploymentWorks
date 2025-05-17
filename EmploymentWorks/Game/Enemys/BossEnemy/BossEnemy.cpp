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

#include "Game/Observer/Enemy/EnemyMessenger.h"
#include "Libraries/MyLib/DebugString.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
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
	,m_isActives{true}
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
/// �f�X�g���N�^
/// </summary>
BossEnemy::~BossEnemy()
{


	m_actionList.clear();
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
void BossEnemy::AddPointer(Player* player, StageObjectManager* stageObjectManager)
{


	m_player = player;

	m_stageObjectmanger = stageObjectManager;

	m_beam->AddPointer(this,player);
}

void BossEnemy::ChangeAction(const std::string actionName)
{

	auto it = m_actionList.find(actionName);

	if (it != m_actionList.end())
	{

		if (m_action.second != nullptr)
		{
			m_action.second->Exit();
		}

		m_action.first = actionName;

		m_action.second = it->second.get();

		m_action.second->Enter();
		

	}


}


/// <summary>
/// ������
/// </summary>
void BossEnemy::Initialize()
{

	EnemyEntity::Initialize();

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();



	//�uBody�v�𐶐�����
	AddChild(std::make_unique<BossEnemyBottom>(BaseEntity::GetCommonResources(),
		this,
		this,
		Params::BOSSENEMY_BODY_SCALE,
		Params::BOSSENEMY_BODY_POSITION,
		Params::BOSSENEMY_BODY_ROTATION));

	//�A�j���[�V�����f�[�^�̓ǂݍ���
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
	
	////�e�p�[�c�ɃA�j���[�V������o�^
	SetAnimationData("Idle", m_animationDatas,"", true);
	SetAnimationData("FallDown", m_animationDatas);
	SetAnimationData("BeamAttack", m_animationDatas);
	SetAnimationData("BeamAttackEnd", m_animationDatas);
	SetAnimationData("Move", m_animationDatas);
	SetAnimationData("SwingDown", m_animationDatas);
	SetAnimationData("Barrier", m_animationDatas);
	SetAnimationData("BarrierEnd", m_animationDatas);
	SetAnimationData("JumpCharge", m_animationDatas);


	//�e�A�N�V�����̍쐬
	m_actionList["JumpAttack"] = std::make_unique<BossJumpAttackAction>(BaseEntity::GetCommonResources(),this,m_player);
	m_actionList["RushAttack"] = std::make_unique<BossRushAttackAction>(BaseEntity::GetCommonResources(),this,m_player);
	m_actionList["BarrierDefense"] = std::make_unique<BarrierDefenseAction>(BaseEntity::GetCommonResources(), this,m_barrier.get());
	m_actionList["BeamAttack"] = std::make_unique<BossBeamAttackAction>(BaseEntity::GetCommonResources(), this, m_beam.get(),m_player);

	m_actionList["Walking"] = std::make_unique<WalkingActionComtroller>(BaseEntity::GetCommonResources(), this,m_player);

	m_actionList["SwingDown"] = std::make_unique<SwingDownAttackAction>(BaseEntity::GetCommonResources(), this);


	ChangeAction("JumpAttack");

	m_behavior->AddPointer(m_player, this);

	//������
	m_behavior->Initialize(BaseEntity::GetCommonResources());
	
	m_beam->Initialize();

	m_barrier->Initialize();

	m_shadow->Initialize(device, context, states);

	//�����蔻��̍쐬
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), Params::BOSSENEMY_SPHERE_COLLIDER_SIZE * BaseEntity::GetScale().x);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Params::BOSSENEMY_BOX_COLLIDER_SIZE * BaseEntity::GetScale());

	m_gravity = Params::GRAVITY;

	m_hp = Params::BOSSENEMY_MAX_HP;

	Messenger::GetInstance()->Rigister(GameMessageType::BossBeamAttackEnd, this);

	//
	EnemyMessenger::GetInstance()->Rigister(GetID(), this);


	m_target = m_player;

	BaseEntity::GetID();
	


}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BossEnemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//�I�u�W�F�N�g���`�悪�����Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}


	EnemyEntity::Render(view, projection);

	CollisionEntity::GetBounding()->DrawBoundingSphere(BaseEntity::GetPosition(), view, projection);
	CollisionEntity::GetBounding()->DrawBoundingBox(BaseEntity::GetPosition(), view, projection);

	//�p�[�c�̕`��
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

	// ���@�̉e��`�悷��
	m_shadow->Render(context, states, view, projection, shadowPos, Params::BOSSENEMY_SHADOW_RADIUS * BaseEntity::GetScale().x);

	//////// �f�o�b�O����\������
	//auto debugString = BaseEntity::GetCommonResources()->GetDebugString();
	//debugString->AddString("Pos %f" ,BaseEntity::GetPosition().x);
	//debugString->AddString("Pos %f" , BaseEntity::GetPosition().y);
	//debugString->AddString("X %d" , m_velocity.x);
	//debugString->AddString("Y %d" , m_velocity.y);


}


/// <summary>
/// �����蔻��N���X�֒ǉ�
/// </summary>
void BossEnemy::AddCollision(CollisionManager* collsionManager)
{
	//�R���W�����}�l�[�W���[�ɒǉ�
	collsionManager->AddCollsion(this);

	for (auto& part : CompositeEntity::GetParts())
	{
		part->AddCollision(collsionManager);
	}

	m_beam->AddCollionManager(collsionManager);

	m_barrier->AddCollision(collsionManager);

}
/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void BossEnemy::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	UNREFERENCED_PARAMETER(tag);
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::None:
			break;
		case CollisionEntity::CollisionTag::Player:
			break;
		case CollisionEntity::CollisionTag::PlayerParts:
			break;
		case CollisionEntity::CollisionTag::Stage:
			m_isGrounded = true;
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

void BossEnemy::OnCollisionStay(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::Stage:
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

void BossEnemy::OnCollisionExit(CollisionEntity* object, CollisionTag tag)
{

	switch (tag)
	{
		case CollisionEntity::CollisionTag::Stage:
			m_isGrounded = false;
			break;
		default:
			break;
	}

}



/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BossEnemy::Update(const float& elapsedTime)
{

	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	if (m_hp > 0)
	{
		m_beam->Update(elapsedTime);
		m_barrier->Update(elapsedTime);
	}




	if (m_action.second->Update(elapsedTime) == IAction::ActionState::End)
	{
		//�r�w�C�r�A�c���[�̍X�V
		m_behavior->Update(elapsedTime);

	 }	

	CollisionEntity::Update(elapsedTime);
	
	CollisionEntity::GetBounding()->Update(BaseEntity::GetPosition());

	//�p�[�c�̍X�V
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Update(elapsedTime);
	}



}

/// <summary>
/// �A�j���[�V�����̓o�^
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
/// <param name="datas">�A�j���[�V�����̃f�[�^</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="isNormalAnimation">�����A�j���[�V�������ǂ���</param>
void BossEnemy::SetAnimationData(std::string animationType, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas, const std::string& partsName, bool isNormalAnimation)
{
	CharacterEntity::SetAnimationData(animationType, datas, partsName, isNormalAnimation);

	//�p�[�c�ɃA�j���[�V������o�^
	for (auto& part : CompositeEntity::GetParts())
	{
		part->SetAnimationData(animationType, datas, partsName, isNormalAnimation);
	}



}

/// <summary>
/// �A�j���[�V�����̕ύX
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
void BossEnemy::ChangeAnimation(std::string animationType)
{
	CharacterEntity::ChangeAnimation(animationType);
	//�p�[�c�̃A�j���[�V������ύX
	for (auto& part : CompositeEntity::GetParts())
	{
		part->ChangeAnimation(animationType);
	}

}



/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">���</param>
/// <param name="datas">�f�[�^</param>
void BossEnemy::Notify(const Telegram<GameMessageType>& telegram)
{
	
	switch (telegram.messageType)
	{
		case GameMessageType::BossBeamAttackEnd:
			break;
		default:
			break;
	}

}


void BossEnemy::Notify(const Telegram<EnemyMessageType>& telegram)
{


	switch (telegram.messageType)
	{
		case EnemyMessageType::BarrierDefense:
			ChangeAction("BarrierDefense");
			break;
		case EnemyMessageType::BeamAttack:
			ChangeAction("BeamAttack");
			break;
		case EnemyMessageType::JumpAttack:
			ChangeAction("JumpAttack");

			break;
		case EnemyMessageType::SwingDown:
			ChangeAction("SwingDown");
			break;
		case EnemyMessageType::Walking:
			ChangeAction("Walking");
			break;
		default:
			break;
	}




}



