#pragma once
#include "GameBase/Interface/IState.h"

class BirdEnemyStateMachine;
class BirdEnemy;


class BirdEnemyMove :public IState
{
public:
	//�R���X�g���N
	BirdEnemyMove(BirdEnemyStateMachine* stateMachine, BirdEnemy* birdEnemy);
	//�f�X�g���N�^
	~BirdEnemyMove() override;

	// �X�V����
	void Update(const float& deltaTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	//���G
	BirdEnemy* m_birdEnemy;
	//�X�e�[�g�}�V��
	BirdEnemyStateMachine* m_stateMahine;


	//���߂̍��W
	DirectX::SimpleMath::Vector3 m_startPosition;
	//�I���̍��W
	DirectX::SimpleMath::Vector3 m_endPosition;
	//����
	float m_time;

};

#pragma once
