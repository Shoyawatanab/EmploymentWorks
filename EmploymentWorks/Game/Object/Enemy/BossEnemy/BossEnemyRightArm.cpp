#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyRightArm.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyHead.h"
#include "Game/DetectionCollision/CollisionManager.h"


void BossEnemyRightArm::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);

}

void BossEnemyRightArm::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
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

void BossEnemyRightArm::Damage(const int damage)
{
	BossEnemyBase::Damage(damage);

}

// �R���X�g���N�^
BossEnemyRightArm::BossEnemyRightArm(CommonResources* resources, BossEnemyBase* parent,
	const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, 
	const DirectX::SimpleMath::Quaternion& initialAngle, int partsHp)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle,partsHp),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyRightArmParts{},
	m_worldMatrix{},
	m_BossEnemyRightArmCenter{}
{
}

// �f�X�g���N�^
BossEnemyRightArm::~BossEnemyRightArm()
{
	Finalize();
}

// ����������
void BossEnemyRightArm::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyArm.cmo", *fx);

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
	BossEnemyBase::CreateBounding(m_currentPosition, m_currentAngle, Vector3(0.6f, 0.9f, 0.6f) * m__currentScale, 1.5f * m__currentScale.x);


}


// �X�V����
void BossEnemyRightArm::Update(const float& elapsdTime)
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
	//�o�E���f�B���O�̍��W�̍X�V
	BossEnemyBase::BoundingUdate(m_currentPosition, m_currentAngle);

	// �C�����i���X�V����
	BossEnemyBase::Update(elapsdTime);
}

// �`�悷��
void BossEnemyRightArm::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BossEnemyRightArm::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_BossEnemyRightArmParts.clear();
}

// �C�e���`���[�W����
void BossEnemyRightArm::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere BossEnemyRightArm::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere BossEnemyRightArmBoundingSphere;
	// ���E���̔��a��ݒ肷��
	BossEnemyRightArmBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return BossEnemyRightArmBoundingSphere;
}

