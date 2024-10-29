#include "pch.h"
#include "Game/Player/Player.h"
//#include "PlayScene.h"
#include "Game/Player/PlayerBody.h"

// �R���X�g���N�^
Player::Player(CommonResources* resources,IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	PlayerBase(resources,parent, this, initialScale,DirectX::SimpleMath::Vector3::Zero, initialAngle),
	m__currentScale{initialScale},
	m_currentPosition{initialPosition},
	m_currentAngle{initialAngle},
	m_PlayerParts{},
	m_worldMatrix{},
	m_PlayerCenter{}
{
}

// �f�X�g���N�^
Player::~Player()
{
	Finalize();
}

// ����������
void Player::Initialize()
{
	using namespace DirectX::SimpleMath;

	//�uBody�v�𐶐�����
	Attach(std::make_unique<PlayerBody>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(0.0f, -0.6f, 0.0f), Quaternion::Identity));

	//std::vector<PlayerBase::AnimationKeyFrame> animation;

	//animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	//animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,5),
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(15),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
	//	, 2.8f });            //�r�̐U��グ

	////�A�j���[�V������o�^
	//PlayerBase::SetAnimations(animation, "FallDown");



}



// �L�[�{�[�h�C�x���g����������
void Player::HandleKeyboardEvent()
{
	using namespace DirectX::SimpleMath;

	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();




	// [C] �L�[�Łu�C�e�v���`���[�W����
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keyboard::C))
	{
		RegistrationRungingAnimation("FallDown");

	}



}

// �X�V����
void Player::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);

	//// �L�[�{�[�h�C�x���g����������
	HandleKeyboardEvent();

	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();


	//�傫����ς���ƃA�j���[�V�����̈ʒu�������̂Œ���
	//m_currentAngle *= Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.1f), 0, DirectX::XMConvertToRadians(0.0f));
	//m_currentPosition.z += 0.01f;

	if (PlayerBase::AnimationUdate(elapsdTime) == AnimationStage::Runngin)
	{
		m_currentPosition.y -= 0.45f * elapsdTime;
		m_currentPosition.z += 0.5f * elapsdTime;
	}

	//m_currentPosition += PlayerBase::GetAnimationPosition();

	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keyboard::D))
	{
	}

	// �C�����i���X�V����
	PlayerBase::Update(elapsdTime);
}

// �`�悷��
void Player::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	// �C�����i��`�悷��
	PlayerBase::Render(view, projection);
}

// �㏈�����s��
void Player::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_PlayerParts.clear();
}

// �C�����E�����쐬����
DirectX::BoundingSphere Player::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere PlayerBoundingSphere;
	// ���E���̔��a��ݒ肷��
	PlayerBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return PlayerBoundingSphere;
}

