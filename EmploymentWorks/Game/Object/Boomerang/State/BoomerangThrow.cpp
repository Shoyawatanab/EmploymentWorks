
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangThrow.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/Object/Boomerang/BoomerangOrbit.h"


const float SPEED = 5.0f;

const DirectX::SimpleMath::Vector3 AxisOfRotation(0,1,0);  //��]��


static float Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

// �R���X�g���N�^
BoomerangThrow::BoomerangThrow(Boomerang* boomerang, Player* player, Enemy* enemy)
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{},
	m_boomerang{ boomerang },
	m_player{ player }
	, m_enemy{ enemy },
	m_index{},
	m_moveSpeed{},
	m_rotateY{},
	m_rotationalMotion{},
	m_transformRatio{},
	m_startIndex{},
	m_totalTime{}
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

	
}



// �X�V����
void BoomerangThrow::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;

	switch (m_state)
	{
		case BoomerangThrow::BoomerangThrowState::SplineCurve:
			SplineCurve(elapsedTime);
			break;
		case BoomerangThrow::BoomerangThrowState::ChaseToPlayer:
			ChaseToPlayer(elapsedTime);
			break;
		default:
			break;
	}

	////��]�^��
	//Quaternion RotationalMotion ;

	////���̍쐬
	//Vector3 axis = m_direction.Cross(AxisOfRotation);
	//
	//if (axis == Vector3::Zero)
	//{
	//	axis = Vector3::UnitY;
	//}

	//float angle = m_rotationalMotion;

	//angle += 2.1f * elapsedTime;

	//RotationalMotion = Quaternion::CreateFromAxisAngle(axis,angle) ;

	//m_rotate = RotationalMotion;
	//m_rotationalMotion = angle;
	m_rotateY += elapsedTime * 20.0f;


	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_rotate);
	m_worldMatrix *= Matrix::CreateRotationY(m_rotateY);
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPosition());

	m_previousFrameDirection = m_direction;

}


void BoomerangThrow::Enter()
{
	using namespace DirectX::SimpleMath;

	m_index = m_spherePos.size() - 1;
	m_startIndex = m_index;
	m_transformRatio = 0;
	m_totalTime = 0;
	m_initialRotate = Quaternion::Identity;
	m_moveSpeed = SPEED;
	m_rotate = Quaternion::Identity;
	m_direction = Vector3::Zero;
	m_rotateY = 0;
	m_rotationalMotion = 0;

	m_initialRotate = m_boomerang->GetRotate();
	m_position = m_boomerang->GetPosition();
	m_previousFrameDirection = m_position;

	m_target = m_enemy->GetPosition();


	m_moveSpherePos = m_boomerang->GetOrbit()->GetMovePos();

	m_state = BoomerangThrowState::SplineCurve;

}

void BoomerangThrow::Exit()
{

}

/// <summary>
/// �X�v���C���Ȑ�
/// </summary>
/// <param name="elapsedTime"></param>
void BoomerangThrow::SplineCurve(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	//m_moveSpeed -= 0.12f * elapsedTime;


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

	m_boomerang->SetPosition(Pos);
	m_direction = Pos - m_previousFrameDirection;

	if (m_transformRatio > 1.0f)
	{
		m_index++;
		m_totalTime = 0.0f;
	}

	//�Ō�̓_�ɂ�����v���C����ǂ������鏈���ɐ؂�ւ���
	if (m_index >= m_startIndex * 2 )
	{

		//��ԑJ��
		//m_boomerang->ChangeState(m_boomerang->GetBoomerangIdling());
		m_state = BoomerangThrowState::ChaseToPlayer;

	}


	m_totalTime += elapsedTime;
}

void BoomerangThrow::ChaseToPlayer(const float& elapsedTime)
{

	DirectX::SimpleMath::Vector3 BoomerangPos = m_boomerang->GetPosition();

	DirectX::SimpleMath::Vector3 PlayerPos = m_player->GetPosition();


	//�i�ޕ���
	DirectX::SimpleMath::Vector3 MoveDirection = PlayerPos - BoomerangPos;
	MoveDirection.Normalize();

	MoveDirection *= SPEED * elapsedTime;

	BoomerangPos += MoveDirection;

	m_boomerang->SetPosition(BoomerangPos);

	float distance = (PlayerPos - BoomerangPos).Length();




	//�߂Â�����
	if (distance <= 2.0f)
	{
		m_boomerang->ChangeState(m_boomerang->GetBoomerangIdling());

	}


}
