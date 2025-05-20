
#include "pch.h"
#include "BoomerangRepelled.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "BoomerangRepelled.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);


/// <summary>
/// �R���X�g���N�^
/// </summary>
BoomerangRepelled::BoomerangRepelled()
	:
	m_worldMatrix{},
	m_boomerang{ }
	,m_pwoer{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangRepelled::~BoomerangRepelled()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BoomerangRepelled::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangRepelled::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	m_position = m_boomerang->GetPosition();
	m_position += m_direction * elapsedTime;

	m_position.y -= m_graivty * elapsedTime;

	m_boomerang->SetPosition(m_position);

	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPosition());

	m_graivty += 5.5f * elapsedTime;

}

void BoomerangRepelled::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangRepelled::Enter()
{
	m_boomerang->SetIsCollisionActive(true);

	m_position = m_boomerang->GetPosition();

	m_direction = m_boomerang->GetPrevPosition();

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



	//m_direction.z *= -1;

	m_direction.Normalize();
	m_position += m_direction;
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangRepelled::Exit()
{

}

void BoomerangRepelled::AddPointer(Boomerang* boomerang)
{
	m_boomerang = boomerang;

}

