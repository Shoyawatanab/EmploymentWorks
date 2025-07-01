#include "pch.h"
#include "BoomerangThrow.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Params.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/Player.h"
#include "Game/MathUtil.h"
#include "Libraries/WataLib/CSV.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Camera/Camera.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/UI/PlayScene/TargetMarker/TargetMarker.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="stateMahine">�X�e�[�g�}�V�[��</param>
/// <param name="boomerang">�u�[������</param>
/// <param name="player">�v���C��</param>
BoomerangThrow::BoomerangThrow(BoomerangStateMachine* stateMahine, Boomerang* boomerang, Player* player)
	:
	m_stateMahine{ stateMahine }
	, m_boomerang{ boomerang }
	,m_player{player}
	,m_throwbasePosition{}
	,m_totalTime{}
	,m_index{}
	,m_state{}
{

	//CSV�������W�̎擾
	m_throwbasePosition = WataLib::CSV::LoadCSVBoomerang();


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangThrow::~BoomerangThrow()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangThrow::Update(const float& deltaTime)
{

	//��]
	Rotation(deltaTime);

	switch (m_state)
	{
		case BoomerangThrow::State::SPINECURVE:		
			SplineCurve(deltaTime);
			break;
		case BoomerangThrow::State::CHASE_TO_PLAYER:
			ChaseToPlayer(deltaTime);
			break;
		default:
			break;
	}

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangThrow::Enter()
{
	using namespace DirectX::SimpleMath;

	m_boomerang->GetTransform()->SetParent(nullptr);


	//��_�̍쐬
	CreateSplineCurvePositon();

	//������
	m_index = 0;
	m_horizontalRotation = Quaternion::Identity;
	m_state = State::SPINECURVE;

	//��]�̏���؂�ւ���
	ChangeRotationDatas(Params::BOOMERANG_THROW_START_ROTATION, Params::BOOMERANG_THROW_MIDDLE_ROTATION);

	//������]���v���C���̉�]��
	m_initialRotation = m_player->GetTransform()->GetRotate();
	//�����蔻��̗L��
	auto aabb = m_boomerang->GetComponent<AABB>();
	aabb->SetActive(true);
	//�e�̗L��
	auto shadow = m_boomerang->GetComponent<RoundShadowComponent>();
	shadow->SetActive(true);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangThrow::Exit()
{
	//�����蔻��̖���
	auto aabb = m_boomerang->GetComponent<AABB>();
	aabb->SetActive(false);
	//�e�̖���
	auto shadow = m_boomerang->GetComponent<RoundShadowComponent>();
	shadow->SetActive(false);


}

void BoomerangThrow::CreateSplineCurvePositon()
{
	using namespace DirectX::SimpleMath;

	std::vector<DirectX::SimpleMath::Vector3> basePosition = m_throwbasePosition;

	//�^�[�Q�b�g�̎擾
	Vector3 target;

	//���b�N�I�����Ă�����
	if (m_player->GetTargetMarker()->GetIsGetLockOn())
	{

		//���b�N�I�����Ă���G�̍��W��
		target = m_player->GetTargetMarker()->GetTargetPosition();

	}
	else
	{

		target = m_boomerang->GetScene()->GetCamera()->GetForwardVector();

		target.Normalize();

		target *= TARGET_LENGTH;

		target += m_player->GetTransform()->GetWorldPosition();

	}


	//�u�[����������^�[�Q�b�g�܂ł̋���
	Vector3 boomerangToTargetDistance = target - m_boomerang->GetTransform()->GetPosition();


	float boomerangToTargetLenght = boomerangToTargetDistance.Length();

	boomerangToTargetDistance = Vector3(0, 0, -1) * boomerangToTargetLenght;

	//�l�𐳂�
	boomerangToTargetDistance.x = std::abs(boomerangToTargetDistance.x);
	//boomerangToTargetDistance.y =std::abs(boomerangToTargetDistance.y);
	boomerangToTargetDistance.z = std::abs(boomerangToTargetDistance.z);

	//�������[����
	boomerangToTargetDistance.y = 0.0f;
	//float�^�ɕϊ��@�����𔼕���
	float boomerangToTargetHalfLenght = boomerangToTargetDistance.Length() / 2;

	//��_��ύX
	for (int i = 0; i < basePosition.size(); i++)
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
		basePosition[i].y = MathUtil::Lerp(m_boomerang->GetTransform()->GetPosition().y, target.y, ratio);

	}

	//��_�̏����ϓ_�ƃv���C���̉�]�@�@�@	��_��180�x����Ă��邽��
	Quaternion rotation = Params::BOOMERANG_THROW_POINT_ROTATE *  m_player->GetTransform()->GetRotate()  ;

	for (int i = 0; i < basePosition.size(); i++)
	{
		//�v���C���̉�]�ɍ��킹��
		basePosition[i] = Vector3::Transform(basePosition[i], rotation);
		//�v���C���̍��W�����Z����
		basePosition[i].x += m_boomerang->GetTransform()->GetPosition().x;
		basePosition[i].z += m_boomerang->GetTransform()->GetPosition().z;
	}


	m_splineCurvePosition = basePosition;



}

/// <summary>
/// �X�v���C���Ȑ�
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BoomerangThrow::SplineCurve(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;
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
	m_boomerang->GetTransform()->SetPosition(position);


	if (ratio > 1.0f)
	{
		//���̓_�Ɠ_�ɕύX
		m_index++;
		m_totalTime = 0.0f;

		//�����܂ōs������
		if ((m_index) % m_splineCurvePosition.size() == m_splineCurvePosition.size() / 2)
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
	m_totalTime += deltaTime;

}

/// <summary>
/// �v���C����ǂ�������
/// </summary>
/// <param name="deltaTime"></param>
void BoomerangThrow::ChaseToPlayer(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	//�u�[�������̍��W���擾
	DirectX::SimpleMath::Vector3 BoomerangPos = m_boomerang->GetTransform()->GetPosition();
	//�v���C���̍��W���擾
	DirectX::SimpleMath::Vector3 PlayerPos = m_player->GetTransform()-> GetPosition();


	//�i�ޕ���
	m_moveDirection = PlayerPos - BoomerangPos;
	m_moveDirection.Normalize();
	//�ǂꂾ���ړ����邩���߂�
	Vector3 moveDirection = m_moveDirection * Params::BOOMERANG_MOVE_SPEED * deltaTime;
	//�ړ��l�̉��Z
	BoomerangPos += moveDirection;
	//���W�̓o�^
	m_boomerang->GetTransform()->SetPosition(BoomerangPos);

	//�v���C���Ƃ̋��������߂�
	float distance = (PlayerPos - BoomerangPos).Length();

	//�߂Â�����
	if (distance <= 0.3f)
	{

		//�u�[�������̏�Ԃ�ʏ��
		m_boomerang->GetStateMAchine()->ChangeState(BoomerangState::IDEL);
		//�u�[�������̃L���b�`�̊���
		SceneMessenger::GetInstance()->Notify(SceneMessageType::BOOMERANG_CATCH);

	}


}


/// <summary>
/// ��]
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BoomerangThrow::Rotation(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;
	//����]
	m_horizontalRotation *= Quaternion::CreateFromAxisAngle(Vector3::Up, Params::BOOMERANG_HORIZONTAL_ROTATION_SPEED * deltaTime);

	//�΂߂̉�]
	Quaternion rotation;
	//�X�^�[�g�n�_���璆�Ԓn�_�܂ł̃x�N�g��
	Vector3 startToMidleVec = m_splineCurvePosition[m_splineCurvePosition.size() / 2] - m_splineCurvePosition[0];
	startToMidleVec.Normalize();
	//�X�^�[�g�n�_����u�[�������܂ł̃x�N�g��
	Vector3 startToBoomerangVec = m_boomerang->GetTransform()->GetPosition() - m_splineCurvePosition[0];
	//���e�x�N�g��
	Vector3 projectionVec = startToMidleVec * startToBoomerangVec.Dot(startToMidleVec);

	Vector3 pos = m_splineCurvePosition[0] + projectionVec;

	float distance = Vector3::Distance(m_splineCurvePosition[0], pos);
	//���������߂�
	float ratio = distance / Vector3::Distance(m_splineCurvePosition[m_splineCurvePosition.size() / 2], m_splineCurvePosition[0]);
	ratio = std::min(ratio, 1.0f);
	//�΂߂̉�]�����߂�
	rotation = Quaternion::Lerp(m_rotationDatas.first, m_rotationDatas.second, ratio);
	//��]�̐ݒ�@���̉�]�@�΂߂̉�]�@�����̉�]
	m_boomerang->GetTransform()->SetRotate(m_horizontalRotation * rotation * m_initialRotation);

}

/// <summary>
/// ��]�f�[�^�̐؂�ւ�
/// </summary>
/// <param name="firstVec">�����l</param>
/// <param name="secondVec">�I���l</param>
void BoomerangThrow::ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec)
{
	m_rotationDatas.first = firstVec;
	m_rotationDatas.second = secondVec;

}
