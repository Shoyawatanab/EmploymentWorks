/*
* ���̓G�̃X�e�[�g�}�V��
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/Enemys/BirdEnemy/State/BirdEnemyIdling.h"
#include "Game/Enemys/BirdEnemy/State/BirdEnemyAttack.h"
#include "Game/Enemys/BirdEnemy/State/BirdEnemyMove.h"


//�O���錾
class Player;
class BirdEnemy;
class BirdEnemyBeam;

class BirdEnemyStateMachine : public IStateMachine<IState>//, public IObserver<EnemyMessageType>
{
public:

	//���݂̏�Ԃ̎擾
	IState* GetCurrentState() { return m_currentState; }

	BirdEnemyldling* GetBirdEnemyldling() { return m_idle.get(); }

	BirdEnemyAttack* GetBirdEnemyAttack() { return m_attack.get(); }

	BirdEnemyMove* GetBirdEnemyMove() { return m_move.get(); }

public:
	//�R���X�g���N�^
	BirdEnemyStateMachine(BirdEnemy* owner, std::vector<std::unique_ptr<BirdEnemyBeam>>& beam);
	//�f�X�g���N�^
	~BirdEnemyStateMachine() override;
	//������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃ̕ύX
	void ChangeState(IState* nextState) override;

	////�G���b�Z���W���[����̒ʒm���󂯎��֐�
	//void Notify(const Telegram<EnemyMessageType>& telegram)  override;


private:
	//���݂̏��
	IState* m_currentState;
	//�ʏ���
	std::unique_ptr<BirdEnemyldling> m_idle;
	//�U��
	std::unique_ptr<BirdEnemyAttack> m_attack;
	std::unique_ptr<BirdEnemyMove> m_move;


	
};