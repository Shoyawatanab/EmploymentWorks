#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"
class CommonResources;

class Boomerang;
class Player;

// PlayerAttackクラスを定義する
class PlayerAttack : public IPlayerState
{
public:

	void ResetGravity() override;


	void SetResouces(CommonResources* resoure) { m_commonResources = resoure; }

public:
	// コンストラクタ
	PlayerAttack();
	// デストラクタ
	~PlayerAttack();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(CommonResources* resoure, Player* player);


private:
	void Attack(float elapsedTime, DirectX::Keyboard::State key);

private:

	// 共通リソース
	CommonResources* m_commonResources;

	Player* m_player;

	float m_graivty;


};

