#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"
class CommonResources;

class Boomerang;
class Player;

// PlayerIdlingクラスを定義する
class PlayerIdling : public IPlayerState
{
public:


	void ResetGravity() override;


	void SetResouces(CommonResources* resoure) { m_commonResources = resoure; }

public:
	// コンストラクタ
	PlayerIdling();
	// デストラクタ
	~PlayerIdling();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(CommonResources* resoure, Player* player);


private:

private:

	// 共通リソース
	CommonResources* m_commonResources;



	Player* m_player;



	float m_graivty;


};

