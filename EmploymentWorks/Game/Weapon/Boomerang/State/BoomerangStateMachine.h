/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/Weapon/Boomerang/State/BoomerangIdle.h"
#include "Game/Weapon/Boomerang/State/BoomerangGetReady.h"
#include "Game/Weapon/Boomerang/State/BoomerangThrow.h"
#include "Game/Weapon/Boomerang/State/BoomerangRepelled.h"
#include "Game/Weapon/Boomerang/State/BoomerangDrop.h"

class TargetMarker;

class BoomerangStateMachine : public IStateMachine
{
public:

	//���݂̏�Ԃ̎擾
	IState* GetCurrentState() { return m_currentState; }
	//�ʏ��Ԃ̎擾
	BoomerangIdle* GetBoomerangIdel() { return m_idle.get(); }
	//�\����Ԃ̎擾
	BoomerangGetReady* GetBoomerangGetReady() { return m_getReady.get(); }
	//������Ԃ̎擾
	BoomerangThrow* GetBoomerangThrow() { return m_throw.get(); }

	BoomerangRepelled* GetBoomerangRepelled() { return m_repelled.get(); }

	BoomerangDrop* GetBoomerangDrop() { return m_drop.get(); }

public:
	//�R���X�g���N�^
	BoomerangStateMachine() ;
	//�f�X�g���N�^
	~BoomerangStateMachine() override;

	//������
	void Initialize(CommonResources* resources, IState* startState = nullptr) override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//��Ԃ̕ύX
	void ChangeState(IState* nextState) override;

	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(Boomerang* boomerang,Player* palyer, TargetMarker* targetMarker, WataLib::TPS_Camera* tpsCamera);



private:
	//���݂̏��
	IState* m_currentState;
	//�ʏ���
	std::unique_ptr<BoomerangIdle> m_idle;
	//�\�����
	std::unique_ptr<BoomerangGetReady> m_getReady;
	//�������
	std::unique_ptr<BoomerangThrow> m_throw;

	std::unique_ptr<BoomerangRepelled> m_repelled;
	
	std::unique_ptr<BoomerangDrop> m_drop;
};