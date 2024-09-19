#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"

class Boomerang;
class Player;

// PlayerUsuallyクラスを定義する
class PlayerUsually : public IPlayerState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// コンストラクタ
	PlayerUsually();
	// デストラクタ
	~PlayerUsually();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(Player* player);


private:
	void Move(float elapsedTime,  DirectX::SimpleMath::Vector3 moveDirection);
	void Attack(float elapsedTime, DirectX::Keyboard::State key);
	void Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);

private:

	Player* m_player;

	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;


	float m_graivty;



};

