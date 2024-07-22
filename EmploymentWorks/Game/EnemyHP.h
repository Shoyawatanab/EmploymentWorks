#pragma once
/*
	@file	EnemyHP.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include <Libraries/MyLib/UserInterface.h>

// 前方宣言
class CommonResources;
class Enemy;




class EnemyHP final 

{
public:

private:

	DX::DeviceResources* m_pDR;

	std::vector < std::unique_ptr<UserInterface>> m_userInterface;

	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;


	Enemy*  m_enemy;

	float m_enemyMaxHP;


public:
	EnemyHP( Enemy* enemy);
	~EnemyHP() ;

	void Initialize(DX::DeviceResources* pDR, int width, int height);
	void Update(float elapsedTime);
	void Render();



	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor
		, UserInterface::Kinds kind);


private:


};
