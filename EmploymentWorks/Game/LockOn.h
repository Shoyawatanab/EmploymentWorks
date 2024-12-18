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
	class GameCameraManager;
	class TPS_Camera;
}



class LockOn final

{
public:
	bool GetIsLOckOn() { return m_isLockOn; }

	DirectX::SimpleMath::Vector3 GetTargetPosition() { return m_target; }

private:

	DX::DeviceResources* m_pDR;

	std::vector < std::unique_ptr<UserInterface>> m_userInterface;

	std::unique_ptr<UserInterface> m_baseWindow;

	int m_windowWidth, m_windowHeight;


	Player* m_player;
	Enemy* m_enemy;
	mylib::TPS_Camera* m_tpsCamera;

	bool m_isLockOn;

	std::vector<ICollisionObject*> m_targetObject;


	DirectX::SimpleMath::Vector3 m_target;

public:
	LockOn();
	~LockOn();

	void Initialize(DX::DeviceResources* pDR, int width, int height);
	void Update(float elapsedTime);
	void Render();

	//クラスに必要な情報（ポインタ）を登録する
	void RegistrationInformation(Player* player, Enemy* enemy, mylib::GameCameraManager* gameCamera);

	//クラスのインスタンス
	void Instances();


	void Add(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor);


	DirectX::SimpleMath::Vector2 FilterWithinRange(const std::vector<DirectX::SimpleMath::Vector3>& points, const DirectX::SimpleMath::Vector2& center, float range);

	void AddTargetObject(ICollisionObject* object) { m_targetObject.push_back(object); }

private:
	//ワールド座標をスクリーン座標に変換する
	DirectX::SimpleMath::Vector2 WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos,
		const DirectX::SimpleMath::Matrix& worldMatrix,
		const DirectX::SimpleMath::Matrix& viewMatrix,
		const DirectX::SimpleMath::Matrix& projectionMatrix,
		int screenWidth, int screenHeight);

	bool IsEnemyInview(const DirectX::SimpleMath::Vector3& playerPos, const DirectX::SimpleMath::Vector3& playerForward, const DirectX::SimpleMath::Vector3& enemyPos);



};
