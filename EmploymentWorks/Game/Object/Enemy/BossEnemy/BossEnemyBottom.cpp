#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyBottom.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftThigh.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyRightThigh.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyPelvis .h"
#include "Game/DetectionCollision/CollisionManager.h"

void BossEnemyBottom::RegistrationCollionManager(CollisionManager* collsionManager)
{

	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);
}

void BossEnemyBottom::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
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
BossEnemyBottom::BossEnemyBottom(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyBottomParts{},
	m_worldMatrix{},
	m_BossEnemyBottomCenter{}
{
}

// �f�X�g���N�^
BossEnemyBottom::~BossEnemyBottom()
{
	Finalize();
}

// ����������
void BossEnemyBottom::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyBottom.cmo", *fx);

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
	BossEnemyBase::CreateBounding(m_currentPosition, m_currentAngle,Vector3(1.65f, 0.5f, 1.1f)* m__currentScale ,2.5f * m__currentScale.x);

	//�A�j���[�V�����̐����@�����@�傫���@���W�@��]�@����
	std::vector<BossEnemyBase::AnimationKeyFrame> animation;
	//test
	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
	, 1.0f });            //���ߎ���
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(90),DirectX::XMConvertToRadians(0))
		, 2.0f });            //���낷

	//�A�j���[�V������o�^
	BossEnemyBase::SetAnimations(animation, "FallDown");

	
	//�uPelvis�v�𐶐�����
	Attach(std::make_unique<BossEnemyPelvis>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.0f, 0.7f, 0.0f), Quaternion::Identity));

	//�uLeftThigh�v�𐶐�����
	Attach(std::make_unique<BossEnemyLeftThigh>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.9f, -0.7f, 0.0f), Quaternion::Identity));
	//�uRightThigh�v�𐶐�����
	Attach(std::make_unique<BossEnemyRightThigh>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(-0.9f, -0.7f, 0.0f), Quaternion::Identity));

}


// �X�V����
void BossEnemyBottom::Update(const float& elapsdTime)
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
void BossEnemyBottom::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BossEnemyBottom::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_BossEnemyBottomParts.clear();
}

// �C�e���`���[�W����
void BossEnemyBottom::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere BossEnemyBottom::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere BossEnemyBottomBoundingSphere;
	// ���E���̔��a��ݒ肷��
	BossEnemyBottomBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return BossEnemyBottomBoundingSphere;
}


