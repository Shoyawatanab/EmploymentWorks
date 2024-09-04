
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangRepelled.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

// �R���X�g���N�^
BoomerangRepelled::BoomerangRepelled(Boomerang* boomerang)
	:
	m_worldMatrix{},
	m_boomerang{boomerang}
{
}

// �f�X�g���N�^
BoomerangRepelled::~BoomerangRepelled()
{

}

// ����������
void BoomerangRepelled::Initialize()
{
	


}


// �X�V����
void BoomerangRepelled::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	m_position = m_boomerang->GetPos();
	m_position += m_direction ;

	m_position.y -= m_graivty;

	m_boomerang->SetPos(m_position);

	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPos());


	m_graivty += 0.005f;

}


void BoomerangRepelled::Enter()
{

	m_position = m_boomerang->GetPos();

	//�e������
	m_direction = m_boomerang->GetPos() - m_boomerang->GetPreviousFramePos();

	m_pwoer = 2.0f;

	//�ォ����
	if (m_direction.y <= 0)
	{
		//�����炠������
		m_graivty = -0.02f;
	}
	else
	{
		//�ォ�炠������
		m_graivty = 0;
	}


	m_position += m_direction;

}

void BoomerangRepelled::Exit()
{

}