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
/// �f�X�g���N�^
/// </summary>
BossEnemy::~BossEnemy()
{
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
	m_animationDatas["Punch"] = json->LoadAnimationData(L"BossEnemy/Punch");
	m_animationDatas["Barrier"] = json->LoadAnimationData(L"BossEnemy/Barrier");
	m_animationDatas["BarrierEnd"] = json->LoadAnimationData(L"BossEnemy/BarrierEnd");
	m_animationDatas["JumpCharge"] = json->LoadAnimationData(L"BossEnemy/JumpCharge");
	
	////�e�p�[�c�ɃA�j���[�V������o�^
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

	//������
	m_behavior->Initialize(BaseEntity::GetCommonResources());
	
	m_beam->Initialize();

	m_barrier->Initialize();

	m_shadow->Initialize(device, context, states);;

	//�����蔻��̍쐬
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
	shadowPos.y = 0.1f;

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();



	// ���@�̉e��`�悷��
	m_shadow->Render(context, states, view, projection, shadowPos, 3.5f);

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
		//�r�w�C�r�A�c���[�̍X�V
		m_behavior->Update(elapsedTime);
		m_beam->Update(elapsedTime);
		m_barrier->Update(elapsedTime);
	}

	m_velocity.y -= m_gravity * elapsedTime ;
	

	Vector3 pos = BaseEntity::GetPosition();
	
	pos += m_velocity;

	BaseEntity::SetPosition(pos);
	
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
/// �r�[���U��
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State BossEnemy::BeamAttack(const float& elapsedTime)
{

	return JumpAttack(elapsedTime);

 
	return Pounding(elapsedTime);

	return m_action["Beam"]->Update(elapsedTime);

	//���ƕǂ̐F��ς���@���z��ǉ����ĉe������

}

/// <summary>
/// ����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
IBehaviorNode::State BossEnemy::Walk(const float& elapsedTime)
{

	if (CharacterEntity::GetCurrentAnimationType() != "Move")
	{
		ChangeAnimation("Move");
		return IBehaviorNode::State::Runngin;
	}

	//�v���C���̍��W�̎擾
	Vector3 playerPosition = m_player->GetPosition();

	//���������߂�
	Vector3 direction = playerPosition - BaseEntity::GetPosition();
	//���K��
	direction.Normalize();

	direction *= Params::BOSSENEMY_MOVE_SPEED * elapsedTime;

	BaseEntity::SetPosition( BaseEntity::GetPosition() + direction);


	return IBehaviorNode::State::Success;
}

/// <summary>
/// �p���`�U��
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>���s����</returns>
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
/// �v���C���̕���������
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State BossEnemy::FacingThePlayer(float elapsdTime)
{

	//������������
	DirectX::SimpleMath::Vector3 direction = m_player->GetPosition() - BaseEntity::GetPosition();
	direction.Normalize();
	//���̓G�̑O����
	DirectX::SimpleMath::Vector3 forward = Vector3::Transform(Vector3::Backward, BaseEntity::GetRotation());
	//forward.Normalize();
	//��]���̍쐬
	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		//���Ȃ�����
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		//���Ȃ牺����
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//�p�x�����߂�
	float moveAngle = forward.Dot(direction);

	//���W�A���l�ɕϊ�
	moveAngle = acosf(moveAngle);

	//�p�x�Ƒ��x�̔�r�ŏ������ق����擾
	moveAngle = std::min(moveAngle, Params::BOSSENEMY_ROTATION_SPEED * elapsdTime);

	//�G�̉�]�̎擾
	DirectX::SimpleMath::Quaternion Rotate = BaseEntity::GetRotation();
	//Y���ɑ΂��ĉ�]��������
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


