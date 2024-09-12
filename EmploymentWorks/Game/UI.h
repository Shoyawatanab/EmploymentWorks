#pragma once
/*
	@file	UI.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include <Libraries/MyLib/UserInterface.h>

// 前方宣言
class CommonResources;
class Enemy;
class Player;

class PlayScene;



class UI final

{
public:

	bool GetIsChangeResultScene() { return m_changeResultScene; }


private:

	// 共通リソース
	CommonResources* m_commonResources;


	std::vector<std::unique_ptr<UserInterface>> m_enemyHP;
	std::vector<std::unique_ptr<UserInterface>> m_playerHP;

	std::unique_ptr<UserInterface> m_clearUI;

	std::unique_ptr<UserInterface> m_gameOverUI;
	std::unique_ptr<UserInterface> m_gameOverReTryUI;
	std::unique_ptr<UserInterface> m_gameOverEndUI;
	std::unique_ptr<UserInterface> m_gameOverArrowUI;


	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;


	Enemy* m_enemy;

	Player* m_player;

	PlayScene* m_playScene;

	float m_clearTime;

	bool m_changeResultScene;


public:
	UI(PlayScene* playScene, Player* player, Enemy* enemy);
	~UI();

	void Initialize(CommonResources* resources, int width, int height);

	void Update(float elapsedTime);

	void GameClearUpdate(float elapsedTime);

	void GameOverUpdate(float elapsedTime);

	void Render();

	void ClearTexRender();

	void GameOverRender();


	void EnemyHPAdd(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor
		, UserInterface::Kinds kind);


	void PlayerHPAdd(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor
		, UserInterface::Kinds kind);

	void ClearTexAdd(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor
		, UserInterface::Kinds kind);

	void GameOverTexAdd(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor
		, UserInterface::Kinds kind);

	void GameOverReTryTexAdd(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor
		, UserInterface::Kinds kind);

	void GameOverEndTexAdd(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor
		, UserInterface::Kinds kind);

	void GameOverArrowTexAdd(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor
		, UserInterface::Kinds kind);


	void CreateEnemyHP();

	void CreatePlayerHP();

	void CreateClearTex();

	void CreateGameOverTex();

private:



};
