#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyRightShoulder.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyRightArmJoint.h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Libraries/MyLib/Animation.h"

void BossEnemyRightShoulder::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);

}

void BossEnemyRightShoulder::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(Pos);

	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:
			break;
		default:
			break;
	}

}

// �R���X�g���N�^
BossEnemyRightShoulder::BossEnemyRightShoulder(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyRightShoulderParts{},
	m_worldMatrix{},
	m_BossEnemyRightShoulderCenter{}
{
}

// �f�X�g���N�^
BossEnemyRightShoulder::~BossEnemyRightShoulder()
{
	Finalize();
}

// ����������
void BossEnemyRightShoulder::Initialize()
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
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPosition();
	BossEnemyBase::Initialize(std::move(m_model));
	//�o�E���f�B���O�̐���
	BossEnemyBase::CreateBounding(m_currentPosition - Vector3(0, 0.45f, 0), m_currentAngle, Vector3(0.67f, 1.0f, 0.67f) * m__currentScale, 1.6f * m__currentScale.x);

	//�A�j���[�V�����̐���
	std::vector<Animation::AnimationKeyFrame> keyFram;
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(15),DirectX::XMConvertToRadians(-70),DirectX::XMConvertToRadians(0))
		, 0.8f });            //�r�̐U��グ
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(15),DirectX::XMConvertToRadians(-70),DirectX::XMConvertToRadians(0))
		, 2.0f });            //���ߎ���

	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //�����l
	//�A�j���[�V�����N���X�̍쐬
	auto animation = std::make_unique<Animation>();
	//�A�j���[�V����KeyFram�̓o�^
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Once);

	BossEnemyBase::SetAnimations(std::move(animation), "Beam");

	keyFram.clear();
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(15),DirectX::XMConvertToRadians(-70),DirectX::XMConvertToRadians(0))
	, 0.0f });


	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 2.0f });            //�����l
	//�A�j���[�V�����N���X�̍쐬
	animation = std::make_unique<Animation>();
	//�A�j���[�V����KeyFram�̓o�^
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Once);

	BossEnemyBase::SetAnimations(std::move(animation), "BeamEnd");



	//�uRightArmJoint�v�𐶐�����
	Attach(std::make_unique<BossEnemyRightArmJoint>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.0, -1.7f, 0.0f),Quaternion::Identity));


}


// �X�V����
void BossEnemyRightShoulder::Update(const float& elapsdTime)
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
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPosition();
	
	//��]������Ƃ���邩��@���̃I�u�W�F�N�g�̒��S����ɐݒ肳��Ă��邩�炻�̕��̂���
	DirectX::SimpleMath::Vector3 pos = Vector3(0, 0.45f, 0);

	pos = Vector3::Transform(pos, m_currentAngle);

	//�o�E���f�B���O�̍��W�̍X�V
	BossEnemyBase::BoundingUdate(m_currentPosition - pos, m_currentAngle);

	// �C�����i���X�V����
	BossEnemyBase::Update(elapsdTime);


}

// �`�悷��
void BossEnemyRightShoulder::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BossEnemyRightShoulder::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_BossEnemyRightShoulderParts.clear();
}

// �C�e���`���[�W����
void BossEnemyRightShoulder::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere BossEnemyRightShoulder::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere BossEnemyRightShoulderBoundingSphere;
	// ���E���̔��a��ݒ肷��
	BossEnemyRightShoulderBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return BossEnemyRightShoulderBoundingSphere;
}

