
#include "pch.h"
#include "Game/Object/Boomerang/BoomerangOrbit.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"



const float SPEED = 5.0f;

const DirectX::SimpleMath::Vector3 AxisOfRotation(0,1,0);  //��]��


static float Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

// �R���X�g���N�^
BoomerangOrbit::BoomerangOrbit(Boomerang* boomerang, Player* player, Enemy* enemy)
	:
	m_boundingSphereLeftLeg{},
	m_boomerang{ boomerang },
	m_player{ player }
	, m_enemy{ enemy },
	m_index{},
	m_moveSpeed{},

	m_transformRatio{},
	m_startIndex{},
	m_totalTime{}
{
}

// �f�X�g���N�^
BoomerangOrbit::~BoomerangOrbit()
{

}

// ����������
void BoomerangOrbit::Initialize(CommonResources* resources)
{
	using namespace DirectX::SimpleMath;

	m_commonResources = resources;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();


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

	m_primitveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);


	m_moveSpeed = SPEED;
	m_initialRotate = Quaternion::Identity;
	m_direction = Vector3::Zero;

}



// �X�V����
void BoomerangOrbit::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;



	m_index = m_spherePos.size() - 1;
	m_startIndex = m_index;
	m_transformRatio = 0;
	m_totalTime = 0;

	m_initialRotate = m_boomerang->GetRotate();
	m_position = m_boomerang->GetPosition();

	m_target = m_enemy->GetPosition();

	m_linePos.clear();




	Matrix SphereMatrix = Matrix::Identity;
	SphereMatrix *= Matrix::CreateFromQuaternion(m_initialRotate);
	//�v���C���ƓG�̋���
	Vector3 PlayerToEnemyDistance = m_target - m_player->GetPosition();

	//���b�N�I����Ԃ���Ȃ����
	if (!m_player->GetIsLockOn())
	{
		//�����������Ō��߂����̂ɂ���
		m_target = Vector3(0, 3, 4);
		PlayerToEnemyDistance = m_target;

	}

	//������flaot�ɕϊ����Ĕ����ɂ���
	float PlayerToEnemyLenght = PlayerToEnemyDistance.Length() / 2;

	//��]�̒n�_����]������
	for (int i = 0; i < m_spherePos.size(); i++)
	{
		//��_
		Vector3 Pos = m_spherePos[i];
		//Sphere�ƃ[���n�_�̋���
		Vector3 Distance = Pos - Vector3::Zero;
		//��̋�����float�����ɕϊ�
		float Lenght = Distance.Length();
		//�G�Ƃ̋�����Sphere�Ƃ̋����̔{�������߂�
		float Magnification = PlayerToEnemyLenght / Lenght;
		Distance *= Magnification;
		Pos = Distance;;
		//�����̔��������Z
		Pos.z -= PlayerToEnemyLenght;


		//�ꎞ�I�ɕۑ�����
		m_moveSpherePos[i] = Pos;


	}


	//��������
	for (int i = 0; i < m_spherePos.size(); i++)
	{
		//�����l�_�����ԉ����Ƃ���̋����ƍ��̍��W�̊��������߂�
		float a = (m_moveSpherePos[i].z - m_moveSpherePos[0].z) / (m_moveSpherePos[3].z - m_moveSpherePos[0].z);
		m_moveSpherePos[i].y = Lerp(m_boomerang->GetPos().y, m_target.y, a) - 1;
	}

	for (int i = 0; i < m_spherePos.size(); i++)
	{

		//�v���C���̉�]�����Ƃɉ�]������
		m_moveSpherePos[i] = Vector3::Transform(m_moveSpherePos[i], SphereMatrix);
		//���_����ɂȂ��Ă��邩��u�[�������̈ʒu�����Z����
		m_moveSpherePos[i] += m_position;
	}





	SplineCurve(elapsedTime);



  }


void BoomerangOrbit::Render()
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	if (m_linePos.size() != 0)
	{



		m_primitveBatch->Begin();


		for (int i = 0; i < m_linePos.size() - 1; i++)
		{
			m_primitveBatch->DrawLine(m_linePos[i], m_linePos[i + 1]);
			
		}

		m_primitveBatch->End();

	}


}


void BoomerangOrbit::Finalize()
{

}

/// <summary>
/// �X�v���C���Ȑ�
/// </summary>
/// <param name="elapsedTime"></param>
void BoomerangOrbit::SplineCurve(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	while (m_index <= m_startIndex * 2 + 1)
	{

		float distance = (m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()] -
			m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()]).Length();
		//�ړ�����
		m_transformRatio = m_totalTime * m_moveSpeed / distance;

		Vector3 Pos = m_boomerang->GetPosition();
		Pos = Vector3::CatmullRom(
			m_moveSpherePos[(m_index + 0) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 3) % m_moveSpherePos.size()],
			m_transformRatio
		);

		DirectX::VertexPositionColor linePos;
		linePos.position = Pos;

		m_linePos.emplace_back(linePos);

		if (m_transformRatio > 1.0f)
		{
			m_index++;
			m_totalTime = 0.0f;
		}




		m_totalTime += elapsedTime;
	}
}