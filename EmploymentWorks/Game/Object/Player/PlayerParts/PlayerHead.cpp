#include "pch.h"
#include "Game/Object/Player/PlayerParts/PlayerHead.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Libraries/MyLib/Animation.h"



void PlayerHead::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);
}

// �R���X�g���N�^
PlayerHead::PlayerHead(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	PlayerBase(resources, parent, initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_PlayerHeadParts{},
	m_worldMatrix{},
	m_PlayerHeadCenter{}
{
}

// �f�X�g���N�^
PlayerHead::~PlayerHead()
{
	Finalize();
}

// ����������
void PlayerHead::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = PlayerBase::GetResources()->GetDeviceResources()->GetD3DDevice();

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerHead.cmo", *fx);


	//���݂̑傫�����X�V�@���̃N���X�̑傫���Ɛe�̑傫��
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//���݂̉�]���X�V�@���̃N���X�̉�]�Ɛe�̉�]
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//��]������W���v�Z����
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//���݂̍��W���X�V�@���̃N���X�̍��W�Ɛe�̍��W �傫����ς��Ă�������ς��Ȃ��悤��Scale��������
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();

	PlayerBase::Initialize(std::move(m_model));






}

// �X�V����
void PlayerHead::Update(const float& elapsdTime)
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
void PlayerHead::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace ::DirectX::SimpleMath;

	//���[���h�s��𐶐�
	m_worldMatrix = Matrix::CreateScale(m__currentScale);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_currentAngle);
	m_worldMatrix *= Matrix::CreateTranslation(m_currentPosition );



	//�`�悷��
	PlayerBase::Render(m_worldMatrix, view,projection);


}

// �㏈�����s��
void PlayerHead::Finalize()
{
	// �폜���镔�i�����Z�b�g����
	m_PlayerHeadParts.clear();
}

// �C�e���`���[�W����
void PlayerHead::ChargeBullets()
{
}

// �C�����E�����쐬����
DirectX::BoundingSphere PlayerHead::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere PlayerHeadBoundingSphere;
	// ���E���̔��a��ݒ肷��
	PlayerHeadBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return PlayerHeadBoundingSphere;
}

