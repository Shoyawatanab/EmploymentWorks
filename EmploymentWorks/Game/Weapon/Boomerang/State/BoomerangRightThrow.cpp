#include "pch.h"
#include "BoomerangRightThrow.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Player/Player.h"
#include "Game/Params.h"

#include "Game/MathUtil.h"
#include "Game/InstanceRegistry.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
BoomerangRightThrow::BoomerangRightThrow(Boomerang* boomerang)
	:
	m_commonResources{}
	,m_splineCurvePosition{}
	,m_index{}
	,m_totalTime{}
	,m_state{}
	,m_rotationDatas{}
	,m_horizontalRotation{}
	,m_initialRotation{}
	,m_moveDirection{}
	, m_boomerang{boomerang}
	, m_player{}
	, m_targetMarker{}
	, m_tpsCamera{}

{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangRightThrow::~BoomerangRightThrow()
{
}



/// <summary>
/// �X�v���C���Ȑ��̊�_�̍쐬
/// </summary>
void BoomerangRightThrow::CreateSplineCurvePositon()
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

		//target = m_tpsCamera->GetCameraForward();

		//target.Normalize();

		//target *= TARGET_LENGTH;

		//target += m_tpsCamera->GetTargetPosition();

	}	
	

	//�u�[����������^�[�Q�b�g�܂ł̋���
	Vector3 boomerangToTargetDistance = target - m_boomerang->GetPosition();
	

	float boomerangToTargetLenght = boomerangToTargetDistance.Length();

	boomerangToTargetDistance = Vector3(0, 0, -1) * boomerangToTargetLenght;

	//�l�𐳂�
	boomerangToTargetDistance.x =std::abs(boomerangToTargetDistance.x);
	//boomerangToTargetDistance.y =std::abs(boomerangToTargetDistance.y);
	boomerangToTargetDistance.z =std::abs(boomerangToTargetDistance.z);

	//�������[����
	boomerangToTargetDistance.y = 0.0f;
	//float�^�ɕϊ��@�����𔼕���
	float boomerangToTargetHalfLenght = boomerangToTargetDistance.Length() /2;

	//��_��ύX
	for(int i = 0; i < basePosition.size(); i++)
	{

		//��_���璆�S�܂ł̒��������߂�
		float lenght = basePosition[i].Length();
		//���������߂�
		float ratio = (lenght == 0.0f) ? 0.0f : boomerangToTargetHalfLenght / lenght;
		//���������ƂɊ�_��ύX
		basePosition[i] *= ratio;

		basePosition[i] -= boomerangToTargetDistance / 2;

	}

	for (int i = 0; i < basePosition.size(); i++)
	{

		//��ԉ�����_�Ƃ̊��������߂�
		float ratio = basePosition[i].z / basePosition[basePosition.size() / 2].z;
		//�����̒���
		basePosition[i].y = MathUtil::Lerp(m_boomerang->GetPosition().y, target.y, ratio);

		
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


/// <summary>
/// �X�v���C���Ȑ�
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangRightThrow::SplineCurve(const float& elapsedTime)
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
			m_state = State::CHASE_TO_PLAYER;
		}
	}

	//�o�ߎ��Ԃ̉��Z
	m_totalTime += elapsedTime;

}

/// <summary>
/// �v���C����ǂ�������
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangRightThrow::ChaseToPlayer(const float& elapsedTime)
{
	//�u�[�������̍��W���擾
	DirectX::SimpleMath::Vector3 BoomerangPos = m_boomerang->GetPosition();
	//�v���C���̍��W���擾
	DirectX::SimpleMath::Vector3 PlayerPos = m_player->GetPosition();


	//�i�ޕ���
	m_moveDirection = PlayerPos - BoomerangPos;
	m_moveDirection.Normalize();
	//�ǂꂾ���ړ����邩���߂�
	Vector3 moveDirection = m_moveDirection * Params::BOOMERANG_MOVE_SPEED * elapsedTime;
	//�ړ��l�̉��Z
	BoomerangPos += moveDirection;
	//���W�̓o�^
	m_boomerang->SetPosition(BoomerangPos);

	//�v���C���Ƃ̋��������߂�
	float distance = (PlayerPos - BoomerangPos).Length();

	//�߂Â�����
	if (distance <= 2.0f)
	{
		//��ԕω�
		//m_boomerang->GetBoomerangStatemachine()->ChangeState(m_boomerang->GetBoomerangStatemachine()->GetBoomerangIdel());
		m_state = State::PASSING_THROUGH;
	}


}

/// <summary>
/// �ʉ�
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangRightThrow::PassingThrough(const float& elapsedTime)
{

	Vector3 position = m_boomerang->GetPosition();

	position += m_moveDirection * Params::BOOMERANG_MOVE_SPEED * elapsedTime;

	m_boomerang->SetPosition(position);

}

/// <summary>
/// ��]
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangRightThrow::Rotation(const float& elapsedTime)
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
void BoomerangRightThrow::ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec)
{

	m_rotationDatas.first = firstVec;
	m_rotationDatas.second = secondVec;



}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BoomerangRightThrow::Initialize(CommonResources* resources)
{
	m_commonResources = resources;

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");
	m_targetMarker = InstanceRegistry::GetInstance()->GetRegistryInstance<TargetMarker>("TargetMarker");
	m_tpsCamera = InstanceRegistry::GetInstance()->GetRegistryInstance<WataLib::TPS_Camera>("TPS_Camera");


	
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangRightThrow::Update(const float& elapsedTime)
{
	//��]
	Rotation(elapsedTime);

	switch (m_state)
	{
		case BoomerangRightThrow::State::SPINECURVE:
			SplineCurve(elapsedTime);
			break;
		case BoomerangRightThrow::State::CHASE_TO_PLAYER:
			ChaseToPlayer(elapsedTime);
			//GoStraight(elapsedTime);
			break;
		case BoomerangRightThrow::State::PASSING_THROUGH:
			PassingThrough(elapsedTime);
			break;
		default:
			break;
	}
	

}



/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangRightThrow::Enter()
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
	m_state = State::SPINECURVE;

	//�u�[�������̐e�q�֌W��؂�
	//m_boomerang->SetIsParentActive(false);
	m_boomerang->SetParent(nullptr);

	//��]�̏���؂�ւ���
	ChangeRotationDatas(Params::BOOMERANG_THROW_START_ROTATION, Params::BOOMERANG_THROW_MIDDLE_ROTATION);
	
	//������]���v���C���̉�]��
	m_initialRotation = m_player->GetRotation();

	m_boomerang->SetIsCollisionActive(true);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangRightThrow::Exit()
{
	m_boomerang->SetIsCollisionActive(false);

}



