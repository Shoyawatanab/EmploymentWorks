
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangThrow.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/BossEnemy.h"
#include "Game/Object/Boomerang/BoomerangOrbit.h"


const float SPEED = 10.0f;

const float ROTATESPEED = 100.0f;

const DirectX::SimpleMath::Vector3 AxisOfRotation(0,1,0);  //��]��

const DirectX::SimpleMath::Quaternion STARTROTATE(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, DirectX::XMConvertToRadians(45)));

const DirectX::SimpleMath::Quaternion MIDDLEROTATE(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, DirectX::XMConvertToRadians(0)));

const DirectX::SimpleMath::Quaternion ENDROTATE(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, DirectX::XMConvertToRadians(-45)));


static float Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

// �R���X�g���N�^
BoomerangThrow::BoomerangThrow()
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{},
	m_boomerang{},
	m_player{}
	, m_enemy{},
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

	
	m_startRotate = STARTROTATE;

	m_endRotate = MIDDLEROTATE;

	m_rotateRate = 0;

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
	m_rotateY += elapsedTime * ROTATESPEED;

	//vec13 = maxDistance

	//1�ɂȂ�O�ɖ߂�ɂȂ��Ă��܂�����0.94�ɂ��Ă���
	if (m_rotateRate < 0.999f)
	{
		//�O�ς𗘗p���ċ��������߂�

		Vector3 vec13 = m_moveSpherePos[m_moveSpherePos.size() / 2] - m_startPosition;
		Vector3 vec12 = m_boomerang->GetPosition() - m_startPosition;

		vec13;
		vec13.Normalize();

		Vector3 projection = vec13 * vec12.Dot(vec13);

		Vector3 pos = m_startPosition + projection;

		float distance = Vector3::Distance(m_startPosition, pos);

		m_rotateRate = distance / m_maxDistance;

		m_rotate = Quaternion::Lerp(m_startRotate, m_endRotate, m_rotateRate);

	}
	else
	{
		m_startRotate = m_rotate;

		m_endRotate = ENDROTATE;

		m_rotateRate = 0;
	}



	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	//��]
	m_worldMatrix *= Matrix::CreateRotationY(m_rotateY);
	//�X��
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_rotate);
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPosition());

	m_previousFrameDirection = m_direction;

}


void BoomerangThrow::Enter()
{
	using namespace DirectX::SimpleMath;

	m_index = static_cast<int>(m_spherePos.size() - 1);
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
	m_previousFrameDirection = m_boomerang->GetPosition();


	m_moveSpherePos = m_boomerang->GetOrbit()->GetMovePos();

	m_state = BoomerangThrowState::SplineCurve;

	m_boomerang->SetUseState(Boomerang::UseState::Throw);

	m_startPosition = m_boomerang->GetPosition();

	int index = static_cast<int>( m_moveSpherePos.size() / 2);

	//���������߂�
	m_maxDistance =  Vector3::Distance( m_moveSpherePos[index], m_startPosition);


	m_startRotate = STARTROTATE;

	m_endRotate = MIDDLEROTATE;

	m_rotateRate = 0;


}

void BoomerangThrow::Exit()
{

}

void BoomerangThrow::RegistrationInformation(Boomerang* boomerang, Player* player, Enemy* enemy)
{

	m_boomerang = boomerang;
	m_player = player;
	m_enemy = enemy;

}

/// <summary>
/// �X�v���C���Ȑ�
/// </summary>
/// <param name="elapsedTime"></param>
void BoomerangThrow::SplineCurve(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	//���������߂�
	float distance = (m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()] -
		m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()]).Length();
	//�ړ�����
	m_transformRatio = m_totalTime * m_moveSpeed / distance;

	Vector3 Pos = m_boomerang->GetPosition();
	//�X�v���C���Ȑ������Ƃɍ��W��
	Pos = Vector3::CatmullRom(
			m_moveSpherePos[(m_index + 0) % m_moveSpherePos.size()] ,
			m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 3) % m_moveSpherePos.size()],
			m_transformRatio
		);
	
	//���W�̍X�V
	m_boomerang->SetPosition(Pos);
	
	m_direction = Pos - m_previousFrameDirection;

	//�������P�𒴂����玟�̓_�Ɉړ�
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
