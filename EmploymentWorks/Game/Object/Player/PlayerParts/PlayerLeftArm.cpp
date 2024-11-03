#include "pch.h"
#include "Game/Object/Player/PlayerParts/PlayerLeftArm.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Libraries/MyLib/Animation.h"




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


	//�A�j���[�V�����̐���
	std::vector<Animation::AnimationKeyFrame> keyFram;
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //�����l

	//�A�j���[�V�����N���X�̍쐬
	auto animation = std::make_unique<Animation>();
	//�A�j���[�V����KeyFram�̓o�^
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Loop);

	PlayerBase::SetAnimations(std::move(animation), "Idling");


	//�A�j���[�V�����̐���
	keyFram.clear();
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(90),DirectX::XMConvertToRadians(0))
		, 0.5f });            //�r�̐U��グ
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //�����l
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-90),DirectX::XMConvertToRadians(0))
		, 0.5f });            //���ߎ���
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //�����l

	//�A�j���[�V�����N���X�̍쐬
	animation = std::make_unique<Animation>();
	//�A�j���[�V����KeyFram�̓o�^
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Loop);

	PlayerBase::SetAnimations(std::move(animation), "Walk");

	keyFram.clear();
	//�A�j���[�V�����̐���
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(40),DirectX::XMConvertToRadians(0))
		, 0.5f });            //�r�̐U��グ
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //�����l
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-40),DirectX::XMConvertToRadians(0))
		, 0.5f });            //���ߎ���
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //�����l

	//�A�j���[�V�����N���X�̍쐬
	animation = std::make_unique<Animation>();
	//�A�j���[�V����KeyFram�̓o�^
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Once);

	PlayerBase::SetAnimations(std::move(animation), "Walks");



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

