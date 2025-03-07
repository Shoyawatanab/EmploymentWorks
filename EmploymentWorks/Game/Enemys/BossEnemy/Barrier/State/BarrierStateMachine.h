/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/Enemys/BossEnemy/Barrier/State/BarrierGenerate.h"
#include "Game/Enemys/BossEnemy/Barrier/State/BarrierShrink.h"



class Player;

class BarrierStateMachine : public IStateMachine
{
public:

	//���݂̏�Ԃ̎擾
	IState* GetCurrentState() { return m_currentState; }

	BarrierGenerate* GetBarrierGenerare() { return m_generate.get(); }

	BarrierShrink* GetBarrierShrink() { return m_shrink.get(); }

public:
	//�R���X�g���N�^
	BarrierStateMachine(CommonResources* resources
		, Barrier* barrier);
	//�f�X�g���N�^
	~BarrierStateMachine() override;

	//������
	void Initialize(CommonResources* resources, IState* startState = nullptr) override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//��Ԃ̕ύX
	void ChangeState(IState* nextState) override;

	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(Player* player);


private:
	//���݂̏��
	IState* m_currentState;

	std::unique_ptr<BarrierGenerate> m_generate;

	std::unique_ptr<BarrierShrink> m_shrink;

	
};