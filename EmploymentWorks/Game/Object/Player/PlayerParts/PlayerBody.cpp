#include "pch.h"
#include "Game/Object/Player/PlayerParts/PlayerBody.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Player/PlayerParts/PlayerHead.h"
#include "Game/Object/Player/PlayerParts/PlayerLeftArm.h"
#include "Game/Object/Player/PlayerParts/PlayerLeftFeet.h"
#include "Game/Object/Player/PlayerParts/PlayerRightArm.h"
#include "Game/Object/Player/PlayerParts/PlayerRightFeet.h"


void PlayerBody::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

// �R���X�g���N�^
PlayerBody::PlayerBody(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	PlayerBase(resources, parent, initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_PlayerBodyParts{},
	m_worldMatrix{},
	m_PlayerBodyCenter{}
{
}

// �f�X�g���N�^
PlayerBody::~PlayerBody()
{
	Finalize();
}

// ����������
void PlayerBody::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = PlayerBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerBody.cmo", *fx);

	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();

	PlayerBase::Initialize(std::move(m_model));



	//�uHead�v�𐶐�����
	Attach(std::make_unique<PlayerHead>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(0.0f, 2.5f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0))));
	//�uLeftArm�v�𐶐�����
	Attach(std::make_unique<PlayerLeftArm>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(1.45f, 0.8f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(3))));
	//�uLeftFeet�v�𐶐�����
	Attach(std::make_unique<PlayerLeftFeet>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(0.5f, -1.2f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0))));
	//�uRightArm�v�𐶐�����
	Attach(std::make_unique<PlayerRightArm>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(-1.45f, 0.8f, 0.0f),
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(180), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(3))));
	//�uRightFeet�v�𐶐�����
	Attach(std::make_unique<PlayerRightFeet>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(-0.5f, -1.2f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0))));


	//�A�j���[�V�����̐����@�����@�傫���@���W�@��]�@����
	std::vector<PlayerBase::AnimationKeyFrame> animation;
	//test
	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //�����l
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
	, 1.0f });            //���ߎ���
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(90),DirectX::XMConvertToRadians(0))
		, 2.0f });            //���낷

	//�A�j���[�V������o�^
	PlayerBase::SetAnimations(animation, "FallDown");


	

}


// �X�V����
void PlayerBody::Update(const float& elapsdTime)
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
void PlayerBody::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void PlayerBody::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_PlayerBodyParts.clear();
}

// �C�e���`���[�W����
void PlayerBody::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere PlayerBody::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere PlayerBodyBoundingSphere;
	// ���E���̔��a��ݒ肷��
	PlayerBodyBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return PlayerBodyBoundingSphere;
}


