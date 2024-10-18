#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftThigh.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftLeg.h"
#include "Game/DetectionCollision/CollisionManager.h"


void BossEnemyLeftThigh::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);

}

void BossEnemyLeftThigh::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{

	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:


			break;
		default:
			break;
	}

}

// �R���X�g���N�^
BossEnemyLeftThigh::BossEnemyLeftThigh(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyLeftThighParts{},
	m_worldMatrix{},
	m_BossEnemyLeftThighCenter{}
{
}

// �f�X�g���N�^
BossEnemyLeftThigh::~BossEnemyLeftThigh()
{
	Finalize();
}

// ����������
void BossEnemyLeftThigh::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyThigh.cmo", *fx);

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
	BossEnemyBase::CreateBounding(m_currentPosition - Vector3(0, 0, 0), m_currentAngle, Vector3(0.41f, 0.55f, 0.41f) * m__currentScale, 1.0f * m__currentScale.x);


	//�A�j���[�V�����̐����@�����@�傫���@���W�@��]�@����
	std::vector<BossEnemyBase::AnimationKeyFrame> animation;
	////test
	//animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	//animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-90),DirectX::XMConvertToRadians(0))
	//	, 0.8f });            //���̐U��グ
	//animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-90),DirectX::XMConvertToRadians(0))
	//	, 2.0f });            //���ߎ���
	//animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0.5f),
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-20),DirectX::XMConvertToRadians(0))
	//	, 0.5f });            //���낷


	////�A�j���[�V������o�^
	//BossEnemyBase::SetAnimations(animation, "LeftFootStep");



	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-70),DirectX::XMConvertToRadians(0))
		, 0.2f });            //���̐U��グ
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-70),DirectX::XMConvertToRadians(0))
		, 0.2f });            //���ߎ���
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
		, 0.2f });            //���낷

	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.5f });     

	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
		, 0.2f });            //���̐U��グ
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
		, 0.2f });            //���ߎ���
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
		, 0.2f });            //���낷


	//�A�j���[�V������o�^
	BossEnemyBase::SetAnimations(animation, "Run");


	

	//�uLeftLeg�v�𐶐�����
	Attach(std::make_unique<BossEnemyLeftLeg>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.0f, -0.6f, 0.0f), Quaternion::Identity));

}


// �X�V����
void BossEnemyLeftThigh::Update(const float& elapsdTime)
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
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPos();

	//�o�E���f�B���O�̍��W�̍X�V
	BossEnemyBase::BoundingUdate(m_currentPosition - Vector3(0, 0.0f, 0), m_currentAngle);


	// �C�����i���X�V����
	BossEnemyBase::Update(elapsdTime);
}

// �`�悷��
void BossEnemyLeftThigh::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BossEnemyLeftThigh::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_BossEnemyLeftThighParts.clear();
}

// �C�e���`���[�W����
void BossEnemyLeftThigh::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere BossEnemyLeftThigh::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere BossEnemyLeftThighBoundingSphere;
	// ���E���̔��a��ݒ肷��
	BossEnemyLeftThighBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return BossEnemyLeftThighBoundingSphere;
}

