#include "pch.h"
#include "BoomerangFrontThrow.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Player/Player.h"
#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Params.h"
#include "Game/InstanceRegistry.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BoomerangFrontThrow::BoomerangFrontThrow(Boomerang* boomerang)
	:
	m_commonResources{}
	,m_totalTime{}
	,m_state{}
	,m_boomerang{boomerang}
	,m_player{}
	,m_targetMarker{}
	,m_tpsCamera{}
{


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangFrontThrow::~BoomerangFrontThrow()
{
}






/// <summary>
/// �^�[�Q�b�g�Ɍ�����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>ture:����������  false: �߂��Ȃ�</returns>
bool BoomerangFrontThrow::ChaseToTarget(const float& elapsedTime)
{

	//�u�[�������̍��W���擾
	DirectX::SimpleMath::Vector3 BoomerangPos = m_boomerang->GetPosition();


	//�i�ޕ���
	DirectX::SimpleMath::Vector3 MoveDirection = m_targetPosistion - BoomerangPos;
	MoveDirection.Normalize();
	//�ǂꂾ���ړ����邩���߂�
	MoveDirection *= Params::BOOMERANG_MOVE_SPEED * elapsedTime;
	//�ړ��l�̉��Z
	BoomerangPos += MoveDirection;
	//���W�̓o�^
	m_boomerang->SetPosition(BoomerangPos);

	//�v���C���Ƃ̋��������߂�
	float distance = (m_targetPosistion - BoomerangPos).Length();

	//�߂Â�����
	if (distance <= 0.5f)
	{

		return true;

	}

	return false;

}

/// <summary>
/// ��]
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangFrontThrow::Rotation(const float& elapsedTime)
{
	//����]�����߂�
	Quaternion horizontalRotation = Quaternion::CreateFromAxisAngle(Vector3::UnitY, Params::BOOMERANG_HORIZONTAL_ROTATION_SPEED * elapsedTime);

	m_boomerang->SetRotation(m_boomerang->GetRotation() * horizontalRotation);

	

}

/// <summary>
/// ��]�̃f�[�^�̐؂�ւ�
/// </summary>
/// <param name="firstVec">�����l</param>
/// <param name="secondVec">�I���l</param>
void BoomerangFrontThrow::ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec)
{


	UNREFERENCED_PARAMETER(firstVec);
	UNREFERENCED_PARAMETER(secondVec);


}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BoomerangFrontThrow::Initialize(CommonResources* resources)
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
void BoomerangFrontThrow::Update(const float& elapsedTime)
{
	//��]
	Rotation(elapsedTime);

	switch (m_state)
	{
		case BoomerangFrontThrow::State::SPINECURVE:
			{
			
				if (ChaseToTarget(elapsedTime))
				{
					m_targetPosistion = m_player->GetPosition();
					m_state = State::CHASE_TO_PLAYER;

				}

			}
			break;
		case BoomerangFrontThrow::State::CHASE_TO_PLAYER:
			
			m_targetPosistion = m_player->GetPosition();

			if (ChaseToTarget(elapsedTime))
			{

				m_boomerang->GetBoomerangStatemachine()->ChangeState(m_boomerang->GetBoomerangStatemachine()->GetBoomerangIdel());


			}

			break;
		default:
			break;
	}
	

}

void BoomerangFrontThrow::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangFrontThrow::Enter()
{
	//�u�[�������̐e�q�֌W��؂�
	m_boomerang->SetParent(nullptr);

	//1�u�[�������̍s�񂩂�傫�����W��]�̒��o
	Matrix matrix = m_boomerang->GetWorldMatrix();
	Vector3 scale;
	Vector3 position;
	Quaternion rotation;
	matrix.Decompose(scale,rotation,position);
	m_boomerang->SetScale(scale);
	m_boomerang->SetRotation(Quaternion::Identity);
	m_boomerang->SetPosition(position);

	m_state = State::SPINECURVE;


	//��]�̏���؂�ւ��� �����Ȃ̂�End��]���狁�߂Ă���@
	//ChangeRotationDatas(Params::BOOMERANG_THROW_END_ROTATION, Params::BOOMERANG_THROW_MIDDLE_ROTATION);
	
	m_targetPosistion = m_targetMarker->GetTargetPosition();

	m_boomerang->SetIsCollisionActive(true);
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangFrontThrow::Exit()
{
	m_boomerang->SetIsCollisionActive(false);

}



