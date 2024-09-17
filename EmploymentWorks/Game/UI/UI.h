#pragma once
/*
	@file	UI.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include <Libraries/MyLib/UserInterface.h>
#include "Interface/IUI.h"
#include "Game/UI/State/GmePlayUI.h"
#include "Game/UI/State/GameClearUI.h"
#include "Game/UI/State/GameOverUI.h"

// �O���錾
class CommonResources;
class Enemy;
class Player;

class PlayScene;



class UI final

{
public:

	IUI* GetCurrentUIState() { return m_cuurentState; }
	GamePlayUI* GetGamePlayUI() { return m_playUI.get(); }
	GameClearUI* GetGameClearUI() { return m_clearUI.get(); }
	GameOverUI* GetGameOverUI() { return m_overUI.get(); }


private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;




	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;

	//State
	IUI* m_cuurentState;
	std::unique_ptr<GamePlayUI> m_playUI;
	std::unique_ptr<GameOverUI> m_overUI;
	std::unique_ptr<GameClearUI> m_clearUI;


public:
	UI();
	~UI();

	void Initialize(CommonResources* resources, int width, int height);

	void Update(float elapsedTime);

	//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
	void RegistrationInformation(PlayScene* playScene, Player* player, Enemy* enemy);

	//�N���X�̃C���X�^���X
	void Instances();

	void Render();

	void ChangeState(IUI* nextState);

private:



};
