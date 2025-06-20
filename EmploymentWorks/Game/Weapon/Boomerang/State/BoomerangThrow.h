#pragma once
#include "GameBase/Interface/IState.h"

class BoomerangStateMachine;
class Boomerang;
class Player;

class BoomerangThrow : public IState
{
private:
	//���
	enum  class State
	{
		SPINECURVE      //������
		, CHASE_TO_PLAYER   //�Ԃ��Ă���
	};


	static constexpr float TARGET_LENGTH{ 5.0f };



public:
	//�R���X�g���N�^
	BoomerangThrow(BoomerangStateMachine* stateMahine, Boomerang* boomerang,Player* player);
	//�f�X�g���N�^
	~BoomerangThrow() override;

	// �X�V����
	void Update(const float& deltaTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	//�X�v���C���Ȑ��̊�_�̍쐬
	void CreateSplineCurvePositon();

	//�X�v���C���Ȑ�
	void SplineCurve(const float& deltaTime);
	//�v���C����ǂ�������
	void ChaseToPlayer(const float& deltaTime);


	//��]
	void Rotation(const float& deltaTime);
	//��]���̐؂�ւ�
	void ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec);


private:
	//�u�[������
	Boomerang* m_boomerang;
	//�X�e�[�g�}�V�[��
	BoomerangStateMachine* m_stateMahine;
	//
	Player* m_player;

	//�X�v���C���Ȑ��̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_splineCurvePosition;
	//�Y����
	int m_index;
	//�o�ߎ���
	float m_totalTime;
	//���
	State m_state;
	//��]�̏��
	std::pair<DirectX::SimpleMath::Quaternion, DirectX::SimpleMath::Quaternion> m_rotationDatas;
	//����]
	DirectX::SimpleMath::Quaternion m_horizontalRotation;
	//������]
	DirectX::SimpleMath::Quaternion m_initialRotation;
	//��������
	DirectX::SimpleMath::Vector3 m_moveDirection;
	//������O���̊���W
	std::vector<DirectX::SimpleMath::Vector3> m_throwbasePosition;


};

