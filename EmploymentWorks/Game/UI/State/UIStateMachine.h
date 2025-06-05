/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IUIState.h"
#include "Game/UI/State/GamePlayUI.h"
#include "Game/UI/State/GameEndUI.h"

class Player;
class PlayScene;

class UIStateMachine : public IStateMachine<IUIState>
{
public:
	//�R���X�g���N�^
	UIStateMachine() ;
	//�f�X�g���N�^
	~UIStateMachine() override;

	//������
	void Initialize(CommonResources* resources, IUIState* startState  =nullptr) ;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	//��Ԃ̕ύX
	void ChangeState(IUIState* nextState) ;


	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(PlayScene* playScene);
	//���݂̏�Ԃ̎擾
	IUIState* GetCurrentState() { return m_currentState; }
	//
	GamePlayUI* GetGamePlayUI() { return m_playUi.get(); }
	//
	GameEndUI* GetGameEndUI() { return m_gameEndUI.get(); }





private:
	//���݂̏��
	IUIState* m_currentState;
	//�ʏ���
	std::unique_ptr<GamePlayUI> m_playUi;
	//�N���A
	std::unique_ptr<GameEndUI> m_gameEndUI;
	
};