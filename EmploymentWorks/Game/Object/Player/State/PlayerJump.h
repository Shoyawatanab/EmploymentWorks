#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"
class CommonResources;

class Boomerang;
class Player;

// PlayerJumpクラスを定義する
class PlayerJump : public IPlayerState
{
public:


	void ResetGravity() override;



public:
	// コンストラクタ
	PlayerJump();
	// デストラクタ
	~PlayerJump();
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





};

