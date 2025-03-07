#include "pch.h"
#include "BoomerangThrow.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Player/Player.h"
#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BoomerangThrow::BoomerangThrow()
	:
	m_commonResources{}
	,m_splineCurvePosition{}
	,m_index{}
	,m_totalTime{}
	,m_state{}
	,m_rotationDatas{}
	,m_horizontalRotation{}
	,m_initialRotation{}
{


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangThrow::~BoomerangThrow()
{
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="boomerang">�u�[������</param>
/// <param name="player">�v���C��</param>
/// <param name="targetMarker">�^�[�Q�b�g�}�[�J�[</param>
/// <param name="tpsCamera">TPS�J����</param>
void BoomerangThrow::AddPointer(Boomerang* boomerang, Player* player, TargetMarker* targetMarker,WataLib::TPS_Camera* tpsCamera)
{
	m_boomerang = boomerang;
	m_player = player;
	m_targetMarker = targetMarker;
	m_tpsCamera = tpsCamera;
}

/// <summary>
/// �X�v���C���Ȑ��̊�_�̍쐬
/// </summary>
void BoomerangThrow::CreateSplineCurvePositon()
{

	std::vector<DirectX::SimpleMath::Vector3> basePosition = m_boomerang->GetThrowBasePosition();

	//�^�[�Q�b�g�̎擾
	Vector3 target;

	//���b�N�I�����Ă�����
	if (m_targetMarker->GetIsLockOn())
	{
		//���b�N�I�����Ă���G�̍��W��
		target = m_targetMarker->GetTargetPosition();
	}
	else
	{

		target = m_tpsCamera->GetCameraForward();

		target.Normalize();

		target *= TARGET_LENGTH;

		target += m_tpsCamera->GetTargetPosition();

	}
	
	//�u�[����������^�[�Q�b�g�܂ł̋���
	Vector3 boomerangToTargetDistance = target - m_boomerang->GetPosition();
	//�������[����
	boomerangToTargetDistance.y = 0.0f;
	//float�^�ɕϊ��@�����𔼕���
	float boomerangToTargetLenght = boomerangToTargetDistance.Length();

	//��_��ύX
	for (int i = 0; i < basePosition.size(); i++)
	{
		////��_���璆�S�܂ł̋��������߂�
		//Vector3 distance = basePosition[i] - Vector3::Zero;
		//��_���璆�S�܂ł̒��������߂�
		float lenght = basePosition[i].Length();
		//���������߂�
		float ratio = (lenght == 0.0f) ? 0.0f : boomerangToTargetLenght / lenght;		
		//���������ƂɊ�_��ύX
		basePosition[i] *= ratio;
		//�������u�[�������̈ʒu�ɍ��킹��
		basePosition[i].y = m_boomerang->GetPosition().y;

	}

	for (int i = 0; i < basePosition.size(); i++)
	{
		//��ԉ�����_�Ƃ̊��������߂�
		float ratio = basePosition[i].z / basePosition[basePosition.size() / 2].z;
		//�����̒���
		basePosition[i].y = Lerp(m_boomerang->GetPosition().y, target.y, ratio);
	
	}
 
	Quaternion rotation = m_player->GetRotation();

	for (int i = 0; i < basePosition.size(); i++)
	{
		//�v���C���̉�]�ɍ��킹��
		basePosition[i] = Vector3::Transform(basePosition[i], rotation);
		//�v���C���̍��W�����Z����
		basePosition[i].x += m_boomerang->GetPosition().x;
		basePosition[i].z += m_boomerang->GetPosition().z;
	}


	m_splineCurvePosition = basePosition;

}

float BoomerangThrow::Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

/// <summary>
/// �X�v���C���Ȑ�
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangThrow::SplineCurve(const float& elapsedTime)
{
	//���W�̋��������߂�
	float distance = (m_splineCurvePosition[(m_index + 1) % m_splineCurvePosition.size()]
		- m_splineCurvePosition[(m_index) % m_splineCurvePosition.size()]).Length();
	

	//���������߂�
	float ratio = m_totalTime * Params::BOOMERANG_MOVE_SPEED / distance;

	//�X�v���C���Ȑ����g�p���č��W�����߂�
	Vector3 position = Vector3::CatmullRom(
		m_splineCurvePosition[(m_index - 1) % m_splineCurvePosition.size()],
		m_splineCurvePosition[(m_index + 0) % m_splineCurvePosition.size()],
		m_splineCurvePosition[(m_index + 1) % m_splineCurvePosition.size()],
		m_splineCurvePosition[(m_index + 2) % m_splineCurvePosition.size()],
		ratio
	);

	//���W�̓o�^
	m_boomerang->SetPosition(position);


	if (ratio > 1.0f)
	{
		//���̓_�Ɠ_�ɕύX
		m_index++;
		m_totalTime = 0.0f;

		//�����܂ōs������
		if ((m_index ) % m_splineCurvePosition.size() == m_splineCurvePosition.size() / 2)
		{
			ChangeRotationDatas(Params::BOOMERANG_THROW_MIDDLE_ROTATION, Params::BOOMERANG_THROW_END_ROTATION);
		}

		//�Ō�̊�_�ɗ�����
		if ((m_index) % m_splineCurvePosition.size() == m_splineCurvePosition.size() - 1)
		{
			m_state = State::ChaseToPlayer;
		}
	}

	//�o�ߎ��Ԃ̉��Z
	m_totalTime += elapsedTime;

}

/// <summary>
/// �v���C����ǂ�������
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangThrow::ChaseToPlayer(const float& elapsedTime)
{
	//�u�[�������̍��W���擾
	DirectX::SimpleMath::Vector3 BoomerangPos = m_boomerang->GetPosition();
	//�v���C���̍��W���擾
	DirectX::SimpleMath::Vector3 PlayerPos = m_player->GetPosition();


	//�i�ޕ���
	DirectX::SimpleMath::Vector3 MoveDirection = PlayerPos - BoomerangPos;
	MoveDirection.Normalize();
	//�ǂꂾ���ړ����邩���߂�
	MoveDirection *= Params::BOOMERANG_MOVE_SPEED * elapsedTime;
	//�ړ��l�̉��Z
	BoomerangPos += MoveDirection;
	//���W�̓o�^
	m_boomerang->SetPosition(BoomerangPos);

	//�v���C���Ƃ̋��������߂�
	float distance = (PlayerPos - BoomerangPos).Length();

	//�߂Â�����
	if (distance <= 2.0f)
	{
		//��ԕω�
		m_boomerang->GetBoomerangStatemachine()->ChangeState(m_boomerang->GetBoomerangStatemachine()->GetBoomerangIdel());
	}


}

/// <summary>
/// ��]
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangThrow::Rotation(const float& elapsedTime)
{

	//����]
	m_horizontalRotation *= Quaternion::CreateFromAxisAngle(Vector3::Up, Params::BOOMERANG_HORIZONTAL_ROTATION_SPEED *elapsedTime);

	//�΂߂̉�]
	Quaternion rotation;
	//�X�^�[�g�n�_���璆�Ԓn�_�܂ł̃x�N�g��
	Vector3 startToMidleVec = m_splineCurvePosition[m_splineCurvePosition.size() / 2] - m_splineCurvePosition[0];
	startToMidleVec.Normalize();
	//�X�^�[�g�n�_����u�[�������܂ł̃x�N�g��
	Vector3 startToBoomerangVec = m_boomerang->GetPosition() - m_splineCurvePosition[0];
	//���e�x�N�g��
	Vector3 projectionVec = startToMidleVec * startToBoomerangVec.Dot(startToMidleVec);

	Vector3 pos = m_splineCurvePosition[0] + projectionVec;

	float distance = Vector3::Distance(m_splineCurvePosition[0], pos);
	//���������߂�
	float ratio = distance / Vector3::Distance(m_splineCurvePosition[m_splineCurvePosition.size() / 2] , m_splineCurvePosition[0]);
	ratio = std::min(ratio, 1.0f);
	//�΂߂̉�]�����߂�
	rotation = Quaternion::Lerp(m_rotationDatas.first, m_rotationDatas.second, ratio);
	//��]�̐ݒ�@���̉�]�@�΂߂̉�]�@�����̉�]
	m_boomerang->SetRotation(m_horizontalRotation * rotation * m_initialRotation);
	//m_boomerang->SetRotation(m_horizontalRotation);
}

/// <summary>
/// ��]�̃f�[�^�̐؂�ւ�
/// </summary>
/// <param name="firstVec">�����l</param>
/// <param name="secondVec">�I���l</param>
void BoomerangThrow::ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec)
{

	m_rotationDatas.first = firstVec;
	m_rotationDatas.second = secondVec;



}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BoomerangThrow::Initialize(CommonResources* resources)
{
	m_commonResources = resources;



	
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangThrow::Update(const float& elapsedTime)
{
	//��]
	Rotation(elapsedTime);

	switch (m_state)
	{
		case BoomerangThrow::State::SplineCurve:
			SplineCurve(elapsedTime);
			break;
		case BoomerangThrow::State::ChaseToPlayer:
			ChaseToPlayer(elapsedTime);
			break;
		default:
			break;
	}
	

}

void BoomerangThrow::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangThrow::Enter()
{
	//1�u�[�������̍s�񂩂�傫�����W��]�̒��o
	Matrix matrix = m_boomerang->GetWorldMatrix();
	Vector3 scale;
	Vector3 position;
	Quaternion rotation;
	matrix.Decompose(scale,rotation,position);
	m_boomerang->SetScale(scale);
	m_boomerang->SetRotation(rotation);
	m_boomerang->SetPosition(position);

	//��_�����
	CreateSplineCurvePositon();
	//������
	m_index = 0;
	m_horizontalRotation = Quaternion::Identity;
	m_state = State::SplineCurve;

	//�u�[�������̐e�q�֌W��؂�
	//m_boomerang->SetIsParentActive(false);
	m_boomerang->SetParent(nullptr);

	//��]�̏���؂�ւ���
	ChangeRotationDatas(Params::BOOMERANG_THROW_START_ROTATION, Params::BOOMERANG_THROW_MIDDLE_ROTATION);
	
	//������]���v���C���̉�]��
	m_initialRotation = m_player->GetRotation();
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangThrow::Exit()
{
}



