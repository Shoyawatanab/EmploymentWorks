#include "pch.h"
#include "Game/Object/Player/PlayerParts/PlayerLeftArm.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"




void PlayerLeftArm::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

// �R���X�g���N�^
PlayerLeftArm::PlayerLeftArm(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	PlayerBase(resources, parent, initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_PlayerLeftArmParts{},
	m_worldMatrix{},
	m_PlayerLeftArmCenter{}
{
}

// �f�X�g���N�^
PlayerLeftArm::~PlayerLeftArm()
{
	Finalize();
}

// ����������
void PlayerLeftArm::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = PlayerBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerArm.cmo", *fx);

	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();
	PlayerBase::Initialize(std::move(m_model));



	////�A�j���[�V�����̐����@�����@�傫���@���W�@��]�@����
	std::vector<PlayerBase::AnimationKeyFrame> animation;
	//test
	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(15),DirectX::XMConvertToRadians(-130),DirectX::XMConvertToRadians(0))
		, 0.8f });            //�r�̐U��グ
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(15),DirectX::XMConvertToRadians(-130),DirectX::XMConvertToRadians(0))
	, 2.0f });            //���ߎ���
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(15),DirectX::XMConvertToRadians(-20),DirectX::XMConvertToRadians(0))
		, 0.5f });            //���낷

	//�A�j���[�V������o�^
	PlayerBase::SetAnimations(animation, "SwingingDownBothArms");

	animation.clear();


	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(15),DirectX::XMConvertToRadians(-70),DirectX::XMConvertToRadians(0))
		, 0.8f });            //�r�̐U��グ
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(15),DirectX::XMConvertToRadians(-70),DirectX::XMConvertToRadians(0))
		, 2.0f });            //���ߎ���
	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.8f });            //�����l

	//�A�j���[�V������o�^
	PlayerBase::SetAnimations(animation, "Beam");




}


// �X�V����
void PlayerLeftArm::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);

	//m_leftShoulderAngle *=  Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-0.1f), DirectX::XMConvertToRadians(0.0f));
	
	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();

	//��]������Ƃ���邩��@���̃I�u�W�F�N�g�̒��S����ɐݒ肳��Ă��邩�炻�̕��̂���
	DirectX::SimpleMath::Vector3 pos = Vector3(0, 0.45f, 0);

	pos = Vector3::Transform(pos, m_currentAngle);


	// �C�����i���X�V����
	PlayerBase::Update(elapsdTime);


}

// �`�悷��
void PlayerLeftArm::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace ::DirectX::SimpleMath;
	//���[���h�s��𐶐�
	m_worldMatrix = Matrix::CreateScale(m__currentScale);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_currentAngle);
	m_worldMatrix *= Matrix::CreateTranslation(m_currentPosition);

	//�`�悷��
	PlayerBase::Render(m_worldMatrix, view,projection);

}

// �㏈�����s��
void PlayerLeftArm::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_PlayerLeftArmParts.clear();
}

// �C�e���`���[�W����
void PlayerLeftArm::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere PlayerLeftArm::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere PlayerLeftArmBoundingSphere;
	// ���E���̔��a��ݒ肷��
	PlayerLeftArmBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return PlayerLeftArmBoundingSphere;
}

