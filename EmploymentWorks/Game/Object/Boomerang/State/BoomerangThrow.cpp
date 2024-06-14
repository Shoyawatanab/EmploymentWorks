
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangThrow.h"
#include "Game/Object/Boomerang/Boomerang.h"


const float SPEED = 2.0f;

// �R���X�g���N�^
BoomerangThrow::BoomerangThrow(Boomerang* boomerang, Player* player)
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{},
	m_boomerang{ boomerang },
	m_player{ player }

{
}

// �f�X�g���N�^
BoomerangThrow::~BoomerangThrow()
{

}

// ����������
void BoomerangThrow::Initialize()
{
	// ���r���E���𐶐�����
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// ���r���E���̔��a��ݒ肷��
	m_boundingSphereLeftLeg.Radius = 0.01;

	m_csv = std::make_unique<CSV>();
	m_spherePos =  m_csv->LoadCSVBoomerang();

	for (int i = 0; i < m_spherePos.size(); i++)
	{
		m_moveSpherePos.emplace_back(DirectX::SimpleMath::Vector3());
	}
	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;

	m_moveSpeed = SPEED;
}



// �X�V����
void BoomerangThrow::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;

	SplineCurve(elapsedTime);

	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());

	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPosition());

}


void BoomerangThrow::Enter()
{
	using namespace DirectX::SimpleMath;

	m_index = m_spherePos.size() - 1;
	m_startIndex = m_index;
	m_transformRatio = 0;
	m_totalTime = 0;

	m_rotate = m_boomerang->GetRotate();
	m_position = m_boomerang->GetPosition();

	Matrix SphereMatrix = Matrix::Identity;
	SphereMatrix *= Matrix::CreateFromQuaternion(m_rotate);


	for (int i = 0; i < m_spherePos.size(); i++)
	{
		//m_moveSpherePos[i] = m_spherePos[i]  ;		
		m_moveSpherePos[i] = Vector3::Transform(m_spherePos[i],SphereMatrix);

	}
	

}

void BoomerangThrow::Exit()
{

}

void BoomerangThrow::SplineCurve(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	m_moveSpeed -= 0.12f * elapsedTime;


	float distance = (m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()] -
		m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()]).Length();
	//�ړ�����
	m_transformRatio = m_totalTime * m_moveSpeed / distance;

	Vector3 Pos = m_boomerang->GetPosition();
		Pos = Vector3::CatmullRom(
			m_moveSpherePos[(m_index + 0) % m_moveSpherePos.size()] ,
			m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 3) % m_moveSpherePos.size()],
			m_transformRatio
		);

	m_boomerang->SetPosition(Pos + m_position);


	if (m_transformRatio > 1.0f)
	{
		m_index++;
		m_totalTime = 0.0f;
	}

	if (m_index >= m_startIndex * 2 + 1)
	{

		//��ԑJ��
		m_boomerang->ChangeState(m_boomerang->GetBoomerangIdling());

	}

	//

	m_totalTime += elapsedTime;
}