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
#include "Game/InstanceRegistry.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
BirdEnemy::BirdEnemy(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	EnemyEntity(resources,scale,position,rotation)
	,m_hp{}
	, m_enemyManager{}
	, m_player{}
	,m_shadow{}
	, m_punchTime{}
	,m_beams{}
	,m_stateMachine{}
	,m_beamPosition{}

{


	m_shadow = std::make_unique<WataLib::Shadow>();

	BaseEntity::SetIsGravity(false);

}


/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemy::~BirdEnemy()
{
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

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

	//�e���\�[�X�̎擾
	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	m_stateMachine = std::make_unique<BirdEnemyStateMachine>(this, m_beams);


	//������
	EnemyEntity::Initialize();
	m_stateMachine->Initialize();
	m_hp = Params::BIRDENEMY_HP;
	m_shadow->Initialize(device, context, states);


	//�����蔻��̍쐬
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), Params::BIRDENEMY_SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Params::BIRDENEMY_BOX_COLLIDER_SIZE);

	//�r�[����10����Ă���
	for (int i = 0; i < 10; i++)
	{
		auto beam = std::make_unique<BirdEnemyBeam>(BaseEntity::GetCommonResources(),this);
		beam->Initialize();

		m_beams.push_back(std::move(beam));
	}

	//�̂̐���
	AddChild(std::make_unique<BirdEnemyBody>(BaseEntity::GetCommonResources(),
		this,
		Params::BIRDENEMY_BODY_SCALE,
		Params::BIRDENEMY_BODY_POSITION,
		Params::BIRDENEMY_BODY_ROTATION));


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

	//�p�[�c�̕`��
	for (auto& parts : CompositeEntity::GetParts())
	{
		parts->Render(view, projection);
	}

	//�r�[���̕`��
	for (auto& beam : m_beams)
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

	for (auto& beam : m_beams)
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
		case CollisionEntity::CollisionTag::BOOMERANG:

			m_hp -= Params::BOOMERANG_DAMAGE;


			if (m_hp <= 0)
			{
				if (BaseEntity::GetIsEntityActive())
				{

					EnemyEntity::GetEnemyManager()->DeleteRemainingEnemy(this);
					Vector3 scale = BaseEntity::GetScale();
					Vector3 position = object->GetPosition();
					UnknownDataTwo aa = { static_cast<void*>(&position) ,static_cast<void*>(&scale)};
					Messenger::GetInstance()->Notify(GamePlayMessageType::CREATE_EXPLOSION, &aa);
					BaseEntity::SetIsEntityActive(false);

				}
			}
			else
			{

				Vector3 pos = object->GetPosition();
				Vector3 scale = BaseEntity::GetScale();

				UnknownDataThree aa = { static_cast<void*>(&pos) ,static_cast<void*>(&scale)};

				Messenger::GetInstance()->Notify(GamePlayMessageType::CREATE_HIT_EFFECT, &aa);

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

	//�X�V
	m_stateMachine->Update(elapsedTime);
	CollisionEntity::Update(elapsedTime);

	//�p�[�c�̍X�V
   	for (auto& parts : CompositeEntity::GetParts())
	{
		parts->Update(elapsedTime);
	}

	//�r�[���̍X�V
	for (auto& beam : m_beams)
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
void BirdEnemy::SetAnimationData(const std::string& animationType
	, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas, 
	const std::string& partsName, 
	bool isNormalAnimation)
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
void BirdEnemy::ChangeAnimation(const std::string& animationType)
{
	CharacterEntity::ChangeAnimation(animationType);
	//�p�[�c�̃A�j���[�V������ύX
	for (auto& part : CompositeEntity::GetParts())
	{
		part->ChangeAnimation(animationType);
	}
}






