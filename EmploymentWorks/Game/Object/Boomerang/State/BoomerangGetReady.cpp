
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangGetReady.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

const float HOLDANGLE = 45.0f;

// �R���X�g���N�^
BoomerangGetReady::BoomerangGetReady()
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{},
	m_boomerang{},
	m_player{}
{
}

// �f�X�g���N�^
BoomerangGetReady::~BoomerangGetReady()
{

}

// ����������
void BoomerangGetReady::Initialize()
{
	

}



// �X�V����
void BoomerangGetReady::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	m_boomerang->SetRotate(m_player->GetRotate()) ;

	Vector3 Pos = m_player->GetPosition();
	m_boomerang->SetPosition(Pos);


	//�}�g���N�X�@�q���̌v�Z�@�e�̌v�Z�̏��Ԃł��Ȃ��Ƃ����Ȃ�
	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	m_worldMatrix *= Matrix::CreateRotationZ(XMConvertToRadians(90));  //�u�[�������𗧂Ă�悤�ɂX�O�x��]

	m_worldMatrix *= Matrix::CreateTranslation(GENERATEDISTANCE);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_boomerang->GetRotate());
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPosition());

}


void BoomerangGetReady::Enter()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	Quaternion angle = m_boomerang->GetRotate();

	//Y,X,Z�̏���
	angle *= Quaternion::CreateFromYawPitchRoll(0, 100.5f, 0);

   	m_boomerang->SetRotate(angle);





}

void BoomerangGetReady::Exit()
{

}

void BoomerangGetReady::RegistrationInformation(Boomerang* boomerang, Player* player)
{

	m_boomerang = boomerang;
	m_player = player;

}
