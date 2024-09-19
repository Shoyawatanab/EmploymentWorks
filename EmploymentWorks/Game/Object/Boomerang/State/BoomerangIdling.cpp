
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangIdling.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

// �R���X�g���N�^
BoomerangIdling::BoomerangIdling()
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{},
	m_boomerang{},
	m_player{}
{
}

// �f�X�g���N�^
BoomerangIdling::~BoomerangIdling()
{

}

// ����������
void BoomerangIdling::Initialize()
{
	


}


// �X�V����
void BoomerangIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	m_boomerang->SetRotate(m_player->GetRotate());
	//m_boomerang->SetPosition(m_player->GetPosition() + GENERATEDISTANCE);

	//�}�g���N�X�@�q���̌v�Z�@�e�̌v�Z�̏��Ԃł��Ȃ��Ƃ����Ȃ�
	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	
	m_worldMatrix *= Matrix::CreateRotationZ(XMConvertToRadians(90));  //�u�[�������𗧂Ă�悤�ɂX�O�x��]

	m_worldMatrix *= Matrix::CreateTranslation(GENERATEDISTANCE);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_player->GetRotate());
	m_worldMatrix *= Matrix::CreateTranslation(m_player->GetPosition());

	//���W���X�V
	Vector3 Pos = Vector3::Transform(Vector3::Zero, m_worldMatrix);
	m_boomerang->SetPosition(Pos);

}


void BoomerangIdling::Enter()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_boomerang->SetRotate(m_player->GetRotate());
	//m_boomerang->SetPosition(m_player->GetPosition() + GENERATEDISTANCE);

	//�}�g���N�X�@�q���̌v�Z�@�e�̌v�Z�̏��Ԃł��Ȃ��Ƃ����Ȃ�
	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());

	m_worldMatrix *= Matrix::CreateRotationZ(XMConvertToRadians(90));  //�u�[�������𗧂Ă�悤�ɂX�O�x��]

	m_worldMatrix *= Matrix::CreateTranslation(GENERATEDISTANCE);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_player->GetRotate());
	m_worldMatrix *= Matrix::CreateTranslation(m_player->GetPosition());

	//���W���X�V
	Vector3 Pos = Vector3::Transform(Vector3::Zero, m_worldMatrix);
	m_boomerang->SetPosition(Pos);

}

void BoomerangIdling::Exit()
{

	//using namespace DirectX;
	//using namespace DirectX::SimpleMath;

	//m_boomerang->SetRotate(m_player->GetRotate());
	////m_boomerang->SetPosition(m_player->GetPosition() + GENERATEDISTANCE);

	////�}�g���N�X�@�q���̌v�Z�@�e�̌v�Z�̏��Ԃł��Ȃ��Ƃ����Ȃ�
	//m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());

	//m_worldMatrix *= Matrix::CreateRotationZ(XMConvertToRadians(90));  //�u�[�������𗧂Ă�悤�ɂX�O�x��]

	//m_worldMatrix *= Matrix::CreateTranslation(GENERATEDISTANCE);
	//m_worldMatrix *= Matrix::CreateFromQuaternion(m_player->GetRotate());
	//m_worldMatrix *= Matrix::CreateTranslation(m_player->GetPosition());


	////���W���X�V
	//Vector3 Pos = Vector3::Transform(Vector3::Zero, m_worldMatrix);
	//m_boomerang->SetPosition(Pos);


}

void BoomerangIdling::RegistrationInformation(Boomerang* boomerang, Player* player)
{

	m_boomerang = boomerang;
	m_player = player;

}
