#pragma once
/*
	@file	LockOn.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include <Libraries/MyLib/UserInterface.h>

// 前方宣言
class CommonResources;
class Player;
class Enemy;

namespace mylib
{
	class TPS_Camera;
}



class LockOn final 

{
public:


private:

	DX::DeviceResources* m_pDR;

	std::vector < std::unique_ptr<UserInterface>> m_userInterface;

	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;


	Player* m_player;
	Enemy*  m_enemy;
	mylib::TPS_Camera* m_tpsCamera;

	bool m_isLockOn;


public:
	LockOn(Player* player, Enemy* enemy,mylib::TPS_Camera* tpsCamera);
	~LockOn() ;

	void Initialize(DX::DeviceResources* pDR, int width, int height);
	void Update(float elapsedTime);
	void Render();



	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor);


private:
	//ワールド座標をスクリーン座標に変換する
	DirectX::SimpleMath::Vector2 WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos,
		const DirectX::SimpleMath::Matrix& worldMatrix,
		const DirectX::SimpleMath::Matrix& viewMatrix,
		const DirectX::SimpleMath::Matrix& projectionMatrix,
		int screenWidth, int screenHeight);

	bool IsEnemyInview(const DirectX::SimpleMath::Vector3& playerPos, const DirectX::SimpleMath::Vector3& playerForward, const DirectX::SimpleMath::Vector3& enemyPos);


};
