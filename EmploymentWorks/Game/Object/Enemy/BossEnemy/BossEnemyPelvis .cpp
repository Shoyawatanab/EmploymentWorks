#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyPelvis .h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyTorso.h"
#include "Game/DetectionCollision/CollisionManager.h"


// �R���X�g���N�^
BossEnemyPelvis::BossEnemyPelvis(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyPelvisParts{},
	m_worldMatrix{},
	m_BossEnemyPelvisCenter{}
{
}

// �f�X�g���N�^
BossEnemyPelvis::~BossEnemyPelvis()
{
	Finalize();
}

// ����������
void BossEnemyPelvis::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyPelvis.cmo", *fx);

	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = BossEnemyBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = BossEnemyBase::GetInitialAngle() * BossEnemyBase::GetAnimationRotation() * BossEnemyBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(BossEnemyBase::GetPositonFromParent() + BossEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BossEnemyBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPos();

	BossEnemyBase::Initialize(std::move(m_model));
	// �u�C�������v�𐶐�����
	Attach(std::make_unique<BossEnemyTorso>(BossEnemyBase::GetResources(), this, m__currentScale, Vector3(0.0f, 1.7f, 0.0f), m_currentAngle));


}


// �X�V����
void BossEnemyPelvis::Update(const float& elapsdTime)
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
	// �C�����i���X�V����
	BossEnemyBase::Update(elapsdTime);
}

// �`�悷��
void BossEnemyPelvis::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace ::DirectX::SimpleMath;
	//���[���h�s��𐶐�
	m_worldMatrix = Matrix::CreateScale(m__currentScale);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_currentAngle);
	m_worldMatrix *= Matrix::CreateTranslation(m_currentPosition);
	//�`�悷��
	BossEnemyBase::Render(m_worldMatrix, view,projection);

}

// �㏈�����s��
void BossEnemyPelvis::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_BossEnemyPelvisParts.clear();
}

// �C�e���`���[�W����
void BossEnemyPelvis::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere BossEnemyPelvis::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere BossEnemyPelvisBoundingSphere;
	// ���E���̔��a��ݒ肷��
	BossEnemyPelvisBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return BossEnemyPelvisBoundingSphere;
}

void BossEnemyPelvis::RegistrationCollionManager(CollisionManager* collsionManager)
{

	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);

}

void BossEnemyPelvis::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:
			break;
		default:
			break;
	}

}