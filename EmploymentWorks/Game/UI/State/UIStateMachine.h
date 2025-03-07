/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/UI/State/GamePlayUI.h"
#include "Game/UI/State/GameEndUI.h"

class Player;
class PlayScene;
class EnemyManager;

class UIStateMachine : public IStateMachine 
{
public:
	//�R���X�g���N�^
	UIStateMachine() ;
	//�f�X�g���N�^
	~UIStateMachine() override;

	//������
	void Initialize(CommonResources* resources, IState* startState  =nullptr) override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//��Ԃ̕ύX
	void ChangeState(IState* nextState) override;


	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(Player* player, PlayScene* playScene, EnemyManager* enemyManager);
	//���݂̏�Ԃ̎擾
	IState* GetCurrentState() { return m_currentState; }

	GamePlayUI* GetGamePlayUI() { return m_playUi.get(); }

	GameEndUI* GetGameEndUI() { return m_gameEndUI.get(); }





private:
	//���݂̏��
	IState* m_currentState;
	//�ʏ���
	std::unique_ptr<GamePlayUI> m_playUi;
	//�N���A
	std::unique_ptr<GameEndUI> m_gameEndUI;
	
};