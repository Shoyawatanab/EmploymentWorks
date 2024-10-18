#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyHead.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/DetectionCollision/CollisionManager.h"


void BossEnemyHead::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);

}

void BossEnemyHead::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
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
BossEnemyHead::BossEnemyHead(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyHeadParts{},
	m_worldMatrix{},
	m_BossEnemyHeadCenter{}
{
}

// �f�X�g���N�^
BossEnemyHead::~BossEnemyHead()
{
	Finalize();
}

// ����������
void BossEnemyHead::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyHead.cmo", *fx);


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
	BossEnemyBase::CreateBounding(m_currentPosition,m_currentAngle ,Vector3(0.7f, 0.7f, 0.7f) * m__currentScale, 1.3f * m__currentScale.x);




}

// �X�V����
void BossEnemyHead::Update(const float& elapsdTime)
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
	BossEnemyBase::BoundingUdate(m_currentPosition,m_currentAngle);


	// �C�����i���X�V����
	BossEnemyBase::Update(elapsdTime);
}

// �`�悷��
void BossEnemyHead::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace ::DirectX::SimpleMath;

	//���[���h�s��𐶐�
	m_worldMatrix = Matrix::CreateScale(m__currentScale);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_currentAngle);
	m_worldMatrix *= Matrix::CreateTranslation(m_currentPosition );

	//�o�E���f�B���O�̕`��
	BossEnemyBase::BoundingRender(view, projection);


	//�`�悷��
	BossEnemyBase::Render(m_worldMatrix, view,projection);


}

// �㏈�����s��
void BossEnemyHead::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_BossEnemyHeadParts.clear();
}

// �C�e���`���[�W����
void BossEnemyHead::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere BossEnemyHead::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere BossEnemyHeadBoundingSphere;
	// ���E���̔��a��ݒ肷��
	BossEnemyHeadBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return BossEnemyHeadBoundingSphere;
}

