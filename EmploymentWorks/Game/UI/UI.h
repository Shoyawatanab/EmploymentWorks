#pragma once
/*
	@file	UI.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include <Libraries/MyLib/UserInterface.h>
#include "Interface/IUI.h"
#include "Game/UI/State/GmePlayUI.h"
#include "Game/UI/State/GameClearUI.h"
#include "Game/UI/State/GameOverUI.h"

// 前方宣言
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

	// 共通リソース
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

	//クラスに必要な情報（ポインタ）を登録する
	void RegistrationInformation(PlayScene* playScene, Player* player, Enemy* enemy);

	//クラスのインスタンス
	void Instances();

	void Render();

	void ChangeState(IUI* nextState);

private:



};
