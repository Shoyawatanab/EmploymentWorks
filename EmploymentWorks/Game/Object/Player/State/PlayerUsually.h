#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"
class CommonResources;

class Boomerang;
class Player;

// PlayerUsuallyクラスを定義する
class PlayerUsually : public IPlayerState
{
public:


	void ResetGravity() override;

	void SetResouces(CommonResources* resoure) { m_commonResources = resoure; }

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
	void RegistrationInformation(CommonResources* resoure,Player* player);


private:
	void Move(float elapsedTime,  DirectX::SimpleMath::Vector3 moveDirection);
	void Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);

private:

	// 共通リソース
	CommonResources* m_commonResources;



	Player* m_player;



	float m_graivty;


};

