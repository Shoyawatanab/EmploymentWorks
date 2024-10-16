#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftShoulder.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftArmJoint.h"


void BossEnemyLeftShoulder::RegistrationCollionManager(CollisionManager* collsionManager)
{
}

void BossEnemyLeftShoulder::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

// �R���X�g���N�^
BossEnemyLeftShoulder::BossEnemyLeftShoulder(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyLeftShoulderParts{},
	m_worldMatrix{},
	m_BossEnemyLeftShoulderCenter{}
{
}

// �f�X�g���N�^
BossEnemyLeftShoulder::~BossEnemyLeftShoulder()
{
	Finalize();
}

// ����������
void BossEnemyLeftShoulder::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyShoulder.cmo", *fx);

	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = BossEnemyBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = BossEnemyBase::GetInitialAngle() * BossEnemyBase::GetAnimationRotation() * BossEnemyBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(BossEnemyBase::GetPositonFromParent() + BossEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BossEnemyBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPos();

	BossEnemyBase::Initialize(std::move(m_model));

	//�o�E���f�B���O�̐���
	BossEnemyBase::CreateBounding(m_currentPosition - Vector3(0, 0.45f, 0), m_currentAngle, Vector3(0.67f, 1.0f, 0.67f) * m__currentScale, 1.6f * m__currentScale.x);


	//�A�j���[�V�����̐����@�����@�傫���@���W�@��]�@����
	std::vector<BossEnemyBase::AnimationKeyFrame> animation;
	//test
	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0), 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(-15),DirectX::XMConvertToRadians(-130),DirectX::XMConvertToRadians(0))
		, 0.8f });            //�r�̐U��グ
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(-15),DirectX::XMConvertToRadians(-130),DirectX::XMConvertToRadians(0))
		, 2.0f });            //���ߎ���
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(-15),DirectX::XMConvertToRadians(-20),DirectX::XMConvertToRadians(0))
		, 0.5f });            //���낷


	//�A�j���[�V������o�^
	BossEnemyBase::SetAnimations(animation, "SwingingDownBothArms");


	//�uLeftArmJoint�v�𐶐�����
	Attach(std::make_unique<BossEnemyLeftArmJoint>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.0, -1.7f, 0.0f), Quaternion::Identity));

}


// �X�V����
void BossEnemyLeftShoulder::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);

	//m_leftShoulderAngle *=  Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-0.1f), DirectX::XMConvertToRadians(0.0f));
	
	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = BossEnemyBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = BossEnemyBase::GetInitialAngle() * BossEnemyBase::GetAnimationRotation() * BossEnemyBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(BossEnemyBase::GetPositonFromParent() + BossEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BossEnemyBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPos();

	//�o�E���f�B���O�̍��W�̍X�V
	BossEnemyBase::BoundingUdate(m_currentPosition - Vector3(0, 0.45f, 0), m_currentAngle);


	// �C�����i���X�V����
	BossEnemyBase::Update(elapsdTime);


}

// �`�悷��
void BossEnemyLeftShoulder::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BossEnemyLeftShoulder::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_BossEnemyLeftShoulderParts.clear();
}

// �C�e���`���[�W����
void BossEnemyLeftShoulder::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere BossEnemyLeftShoulder::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere BossEnemyLeftShoulderBoundingSphere;
	// ���E���̔��a��ݒ肷��
	BossEnemyLeftShoulderBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return BossEnemyLeftShoulderBoundingSphere;
}

