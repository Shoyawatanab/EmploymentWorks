#pragma once
/*
	@file	UI.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include <Libraries/MyLib/UserInterface.h>

// �O���錾
class CommonResources;
class Enemy;
class Player;



class UI final 

{
public:


private:

	DX::DeviceResources* m_pDR;

	std::vector<std::unique_ptr<UserInterface>> m_enemyHP;
	std::vector<std::unique_ptr<UserInterface>> m_playerHP;


	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;


	Enemy*  m_enemy;

	Player* m_player;

public:
	UI(Player* player, Enemy* enemy);
	~UI() ;

	void Initialize(DX::DeviceResources* pDR, int width, int height);
	void Update(float elapsedTime);
	void Render();



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


	void CreateEnemyHP();

	void CreatePlayerHP();

private:



};
