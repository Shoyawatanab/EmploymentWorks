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
/// �R���X�g���N
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
/// �f�X�g���N�^
/// </summary>
BirdEnemy::~BirdEnemy()
{
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
void BirdEnemy::AddPointer(Player* player)
{
	m_player = player;

	m_stateMachine->AddPointer(m_player, this);

}

/// <summary>
/// ��]
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemy::Rotate(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	//�G�̌��݂̍��W�̎擾
	Vector3 enemyPosition = BaseEntity::GetPosition();
	//�v���C���̌��݂̍��W�̎擾
	Vector3 playerPosition = m_player->GetPosition();
	//�G����v���C���̕����x�N�g���̌v�Z
	Vector3 toPlayer = playerPosition - enemyPosition;
	//yaw�̌v�Z�@�i���E��]�j
	//xz���ʂœG����v���C���̕��������߂�
	float yaw = atan2(toPlayer.x, toPlayer.z);
	//pitch�̌v�Z�i�㉺��]�j
	//�G����v���C���̃E�ᒺ���������߂�
	float pitch = atan2(toPlayer.y, sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z));

	//yaw pitch�����]���v�Z pitch�͔��]������
	BaseEntity::SetRotation(Quaternion::CreateFromYawPitchRoll(yaw, -pitch, 0.0f));

	Vector3 pos = Vector3::Transform(Params::BIRDENEMY_BEAM_SHOT_POSITION, BaseEntity::GetRotation());

	m_beamPosition = BaseEntity::GetPosition() + pos;;




}


/// <summary>
/// ������
/// </summary>
void BirdEnemy::Initialize()
{

	EnemyEntity::Initialize();

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();





	m_stateMachine->Initialize(BaseEntity::GetCommonResources(), m_stateMachine->GetBirdEnemyldling());

	//�����蔻��̍쐬
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), Params::BIRDENEMY_SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Params::BIRDENEMY_BOX_COLLIDER_SIZE);

	//10����Ă���
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
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BirdEnemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//�I�u�W�F�N�g���`�悪�����Ȃ�
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
		//idling��Ԃ���Ȃ����̂�`�悷��
		if (beam->GetStateMahine()->GetCurrentState() != beam->GetStateMahine()->GetBirdEnemyBeamIdle())
		{

			beam->Render(view, projection);

		}
	}


	DirectX::SimpleMath::Vector3 shadowPos = BaseEntity::GetPosition();
	shadowPos.y = Params::SHADOW_POSITION_Y;




	// ���@�̉e��`�悷��
	m_shadow->Render(context, states, view, projection, shadowPos, Params::BIRDENEMY_SHADOW_RADIUS);


}



/// <summary>
/// �����蔻��ɒǉ�
/// </summary>
/// <param name="collsionManager">�����蔻��N���X</param>
void BirdEnemy::AddCollision(CollisionManager* collsionManager)
{
	//�R���W�����}�l�[�W���[�ɒǉ�
	collsionManager->AddCollsion(this);

	for (auto& beam : m_beam)
	{
		beam->AddCollision(collsionManager);
	}

}

/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
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
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemy::Update(const float& elapsedTime)
{

	//�I�u�W�F�N�g���X�V�������Ȃ�
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


	//�r�[���̍X�V
	for (auto& beam : m_beam)
	{
		beam->Update(elapsedTime);
	}

}

/// <summary>
/// �A�j���[�V�����̓o�^
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
/// <param name="datas">�A�j���[�V�����f�[�^</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="isNormalAnimation">�����A�j���[�V�������ǂ���</param>
void BirdEnemy::SetAnimationData(std::string animationType, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas, const std::string& partsName, bool isNormalAnimation)
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
void BirdEnemy::ChangeAnimation(std::string animationType)
{
	CharacterEntity::ChangeAnimation(animationType);
	//�p�[�c�̃A�j���[�V������ύX
	for (auto& part : CompositeEntity::GetParts())
	{
		part->ChangeAnimation(animationType);
	}
}






