#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"
class CommonResources;

class Boomerang;
class Player;

// PlayerBlownAwayクラスを定義する
class PlayerBlownAway : public IPlayerState
{
public:


	void ResetGravity() override;


public:
	// コンストラクタ
	PlayerBlownAway();
	// デストラクタ
	~PlayerBlownAway();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(CommonResources* resoure, Player* player);


private:
	CommonResources* m_commonResources;



	Player* m_player;


	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector3 m_direction;


	float m_graivty;



};

