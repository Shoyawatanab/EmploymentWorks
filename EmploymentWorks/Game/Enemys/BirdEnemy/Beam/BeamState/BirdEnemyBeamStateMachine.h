/*
* ���̓G�̃r�[���̃X�e�[�g�}�V��
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/Enemys/BirdEnemy/Beam/BeamState/BirdEnemyBeamIdling.h"
#include "Game/Enemys/BirdEnemy/Beam/BeamState/BirdEnemyBeamPreliminaryAction.h"
#include "Game/Enemys/BirdEnemy/Beam/BeamState/BirdEnemyBeamAttack.h"

//�O���錾
class Player;
class BirdEnemy;

class BirdEnemyBeamStateMachine : public IStateMachine
{
public:
	//���݂̏�Ԃ̎擾
	IState* GetCurrentState() { return m_currentState; }
	//
	BirdEnemyBeamIdling* GetBirdEnemyBeamIdle() { return m_idle.get(); }
	//
	BirdEnemyBeamAttack* GetBirdEnemyBeamAttack() { return m_attack.get(); }
	//
	BirdEnemyBeamPreliminaryAction* GetBirdEnemyBeamPreliminaryAction() { return m_preliminaryAction.get(); }

public:
	//�R���X�g���N�^
	BirdEnemyBeamStateMachine(BirdEnemy* enemy, BirdEnemyBeam* beam);
	//�f�X�g���N�^
	~BirdEnemyBeamStateMachine() override;

	//������
	void Initialize() ;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//��Ԃ̕ύX
	void ChangeState(IState* nextState) override;

private:
	//���݂̏��
	IState* m_currentState;
	//�ʏ���
	std::unique_ptr<BirdEnemyBeamIdling> m_idle;
	//�U��
	std::unique_ptr<BirdEnemyBeamAttack> m_attack;
	//�\������
	std::unique_ptr<BirdEnemyBeamPreliminaryAction> m_preliminaryAction;


	
};