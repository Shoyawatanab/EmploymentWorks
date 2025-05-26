/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/Player/State/PlayerIdle.h"
#include "Game/Player/State/PlayerAttack.h"


class Player;

class PlayerStateMachine : public IStateMachine
{
public:

	//���݂̏�Ԃ̎擾
	IState* GetCurrentState() { return m_currentState; }

	PlayerIdle* GetPlayerIdle() { return m_idle.get(); }

	PlayerAttack* GetPlayerAttack() { return m_attack.get(); }

public:
	//�R���X�g���N�^
	PlayerStateMachine(Player* player);
	//�f�X�g���N�^
	~PlayerStateMachine() override;

	//������
	void Initialize(CommonResources* resources, IState* startState = nullptr) ;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//��Ԃ̕ύX
	void ChangeState(IState* nextState) override;


private:
	//���݂̏��
	IState* m_currentState;
	//�ʏ���
	std::unique_ptr<PlayerIdle> m_idle;
	//�U��
	std::unique_ptr<PlayerAttack> m_attack;


	
};