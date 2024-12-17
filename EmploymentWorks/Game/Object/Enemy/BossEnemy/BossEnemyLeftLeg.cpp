#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftLeg.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyHead.h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Libraries/MyLib/Animation.h"


void BossEnemyLeftLeg::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);

}

void BossEnemyLeftLeg::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(Pos);

	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:
			BossEnemyBase::PartsDamage(BossEnemyBase::BOOMERANGDAMEGE);

			break;
		default:
			break;
	}

}

void BossEnemyLeftLeg::Damage(const int damage)
{
	BossEnemyBase::Damage(damage);

}

// �R���X�g���N�^
BossEnemyLeftLeg::BossEnemyLeftLeg(CommonResources* resources, BossEnemyBase* parent,
	const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, 
	const DirectX::SimpleMath::Quaternion& initialAngle, int partsHp)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle,partsHp),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyLeftLegParts{},
	m_worldMatrix{},
	m_BossEnemyLeftLegCenter{}
{
}

// �f�X�g���N�^
BossEnemyLeftLeg::~BossEnemyLeftLeg()
{
	Finalize();
}

// ����������
void BossEnemyLeftLeg::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyLeg.cmo", *fx);

	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = BossEnemyBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = BossEnemyBase::GetInitialAngle() * BossEnemyBase::GetAnimationRotation() * BossEnemyBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(BossEnemyBase::GetPositonFromParent() + BossEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BossEnemyBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPosition();

	BossEnemyBase::Initialize(std::move(m_model));

	//�o�E���f�B���O�̐���
	BossEnemyBase::CreateBounding(m_currentPosition - Vector3(0, 0.5f, 0), m_currentAngle, Vector3(0.4f, 0.55f, 0.4f) * m__currentScale, 1.0f * m__currentScale.x);

	//�A�j���[�V�����̐���
	std::vector<Animation::AnimationKeyFrame> keyFram;
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(90),DirectX::XMConvertToRadians(0))
	, 1.0f });            //���ߎ���
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
		, 2.0f });            //���낷
	//keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //�����l

	//�A�j���[�V�����N���X�̍쐬
	auto animation = std::make_unique<Animation>();
	//�A�j���[�V����KeyFram�̓o�^
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Once);

	BossEnemyBase::SetAnimations(std::move(animation), "FallDown");

}


// �X�V����
void BossEnemyLeftLeg::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);
	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = BossEnemyBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = BossEnemyBase::GetInitialAngle() * BossEnemyBase::GetAnimationRotation() * BossEnemyBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(BossEnemyBase::GetPositonFromParent() + BossEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BossEnemyBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPosition();


	//��]������Ƃ���邩��@
	DirectX::SimpleMath::Vector3 pos = Vector3(0, 0.5f, 0);

	pos = Vector3::Transform(pos, m_currentAngle);

	//�o�E���f�B���O�̍��W�̍X�V
	BossEnemyBase::BoundingUdate(m_currentPosition - pos, m_currentAngle);


	// �C�����i���X�V����
	BossEnemyBase::Update(elapsdTime);
}

// �`�悷��
void BossEnemyLeftLeg::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace ::DirectX::SimpleMath;
	//���[���h�s��𐶐�
	m_worldMatrix = Matrix::CreateScale(m__currentScale);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_currentAngle);
	m_worldMatrix *= Matrix::CreateTranslation(m_currentPosition);

	//�o�E���f�B���O�̕`��
	BossEnemyBase::BoundingRender(view, projection);


	//�`�悷��
	BossEnemyBase::Render(m_worldMatrix, view,projection);

}

// �㏈�����s��
void BossEnemyLeftLeg::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_BossEnemyLeftLegParts.clear();
}

// �C�e���`���[�W����
void BossEnemyLeftLeg::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere BossEnemyLeftLeg::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere BossEnemyLeftLegBoundingSphere;
	// ���E���̔��a��ݒ肷��
	BossEnemyLeftLegBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return BossEnemyLeftLegBoundingSphere;
}

