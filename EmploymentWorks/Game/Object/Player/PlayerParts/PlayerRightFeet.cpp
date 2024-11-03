#include "pch.h"
#include "Game/Object/Player/PlayerParts/PlayerRightFeet.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Libraries/MyLib/Animation.h"


void PlayerRightFeet::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

// �R���X�g���N�^
PlayerRightFeet::PlayerRightFeet(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	PlayerBase(resources, parent, initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_PlayerRightFeetParts{},
	m_worldMatrix{},
	m_PlayerRightFeetCenter{}
{
}

// �f�X�g���N�^
PlayerRightFeet::~PlayerRightFeet()
{
	Finalize();
}

// ����������
void PlayerRightFeet::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = PlayerBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerFeet.cmo", *fx);

	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();

	PlayerBase::Initialize(std::move(m_model));


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
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(45),DirectX::XMConvertToRadians(0))
		, 0.5f });            //�r�̐U��グ
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //�����l
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-45),DirectX::XMConvertToRadians(0))
		, 0.5f });            //���ߎ���
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //�����l

	//�A�j���[�V�����N���X�̍쐬
	animation = std::make_unique<Animation>();
	//�A�j���[�V����KeyFram�̓o�^
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Loop);

	PlayerBase::SetAnimations(std::move(animation), "Walk");



}


// �X�V����
void PlayerRightFeet::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);
	
	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();
	// �C�����i���X�V����
	PlayerBase::Update(elapsdTime);
}

// �`�悷��
void PlayerRightFeet::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void PlayerRightFeet::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_PlayerRightFeetParts.clear();
}

// �C�e���`���[�W����
void PlayerRightFeet::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere PlayerRightFeet::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere PlayerRightFeetBoundingSphere;
	// ���E���̔��a��ݒ肷��
	PlayerRightFeetBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return PlayerRightFeetBoundingSphere;
}

