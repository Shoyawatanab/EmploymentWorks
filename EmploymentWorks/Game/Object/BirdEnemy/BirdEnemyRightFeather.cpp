#include "pch.h"
#include "Game/Object/BirdEnemy/BirdEnemyRightFeather.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/DetectionCollision/CollisionManager.h"


void BirdEnemyRightFeather::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BirdEnemyBase::RegistrationCollionManager(collsionManager);

}

void BirdEnemyRightFeather::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

// �R���X�g���N�^
BirdEnemyRightFeather::BirdEnemyRightFeather(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BirdEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BirdEnemyRightFeatherParts{},
	m_worldMatrix{},
	m_BirdEnemyRightFeatherCenter{}
{
}

// �f�X�g���N�^
BirdEnemyRightFeather::~BirdEnemyRightFeather()
{
	Finalize();
}

// ����������
void BirdEnemyRightFeather::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BirdEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BirdEnemyFeather.cmo", *fx);

	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = BirdEnemyBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = BirdEnemyBase::GetInitialAngle() * BirdEnemyBase::GetAnimationRotation() * BirdEnemyBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(BirdEnemyBase::GetPositonFromParent() + BirdEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BirdEnemyBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * BirdEnemyBase::GetParent()->GetScale()) + BirdEnemyBase::GetParent()->GetPosition();

	BirdEnemyBase::Initialize(std::move(m_model));

	//�o�E���f�B���O�̐���
	BirdEnemyBase::CreateBounding(m_currentPosition, m_currentAngle,Vector3(0.7f, 0.15f, 0.45f)* m__currentScale ,2.5f * m__currentScale.x);




}


// �X�V����
void BirdEnemyRightFeather::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);
	
	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = BirdEnemyBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = BirdEnemyBase::GetInitialAngle() * BirdEnemyBase::GetAnimationRotation() * BirdEnemyBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(BirdEnemyBase::GetPositonFromParent() + BirdEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BirdEnemyBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * BirdEnemyBase::GetParent()->GetScale()) + BirdEnemyBase::GetParent()->GetPosition();

	//�o�E���f�B���O�̍��W�̍X�V
	BirdEnemyBase::BoundingUdate(m_currentPosition,m_currentAngle);

	// �C�����i���X�V����
	BirdEnemyBase::Update(elapsdTime);

}

// �`�悷��
void BirdEnemyRightFeather::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace ::DirectX::SimpleMath;
	//���[���h�s��𐶐�
	m_worldMatrix = Matrix::CreateScale(m__currentScale);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_currentAngle);
	m_worldMatrix *= Matrix::CreateTranslation(m_currentPosition);

	//�o�E���f�B���O�̕`��
	//BirdEnemyBase::BoundingRender(view, projection);

	//�`�悷��
	BirdEnemyBase::Render(m_worldMatrix, view,projection);


}

// �㏈�����s��
void BirdEnemyRightFeather::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_BirdEnemyRightFeatherParts.clear();
}

// �C�e���`���[�W����
void BirdEnemyRightFeather::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere BirdEnemyRightFeather::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere BirdEnemyRightFeatherBoundingSphere;
	// ���E���̔��a��ݒ肷��
	BirdEnemyRightFeatherBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return BirdEnemyRightFeatherBoundingSphere;
}


