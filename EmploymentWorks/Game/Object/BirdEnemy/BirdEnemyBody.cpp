#include "pch.h"
#include "Game/Object/BirdEnemy/BirdEnemyBody.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/BirdEnemy/BirdEnemyLeftFeather.h"
#include "Game/Object/BirdEnemy/BirdEnemyRightFeather.h"
#include "Game/DetectionCollision/CollisionManager.h"

void BirdEnemyBody::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BirdEnemyBase::RegistrationCollionManager(collsionManager);
}



void BirdEnemyBody::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

// �R���X�g���N�^
BirdEnemyBody::BirdEnemyBody(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BirdEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BirdEnemyBodyParts{},
	m_worldMatrix{},
	m_BirdEnemyBodyCenter{}
{
}

// �f�X�g���N�^
BirdEnemyBody::~BirdEnemyBody()
{
	Finalize();
}

// ����������
void BirdEnemyBody::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BirdEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BirdEnemyBody.cmo", *fx);

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
	BirdEnemyBase::CreateBounding(m_currentPosition, m_currentAngle,Vector3(0.5f, 0.6f, 1.0f)* m__currentScale ,2.5f * m__currentScale.x);



	

	//�uLeftThigh�v�𐶐�����
	Attach(std::make_unique<BirdEnemyLeftFeather>(BirdEnemyBase::GetResources(), this, BirdEnemyBase::GetInitialScale(), Vector3(0.5f, 0.0f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, DirectX::XMConvertToRadians(180))));
	//�uRightThigh�v�𐶐�����
	Attach(std::make_unique<BirdEnemyRightFeather>(BirdEnemyBase::GetResources(), this, BirdEnemyBase::GetInitialScale(), Vector3(-0.5f,0.0f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, DirectX::XMConvertToRadians(0.0f))));

}


// �X�V����
void BirdEnemyBody::Update(const float& elapsdTime)
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
void BirdEnemyBody::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BirdEnemyBody::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_BirdEnemyBodyParts.clear();
}

// �C�e���`���[�W����
void BirdEnemyBody::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere BirdEnemyBody::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere BirdEnemyBodyBoundingSphere;
	// ���E���̔��a��ݒ肷��
	BirdEnemyBodyBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return BirdEnemyBodyBoundingSphere;
}


