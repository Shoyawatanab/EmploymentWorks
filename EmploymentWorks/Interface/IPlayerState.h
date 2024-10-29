#pragma once
#ifndef IPLAYERSTATE_DEFINED
#define IPLAYERSTATE_DEFINED

// IBoomerangStateインタフェースを定義する(GOF Stateパターン)
class IPlayerState
{
public:
	virtual ~IPlayerState() = default;
	// 初期化する
	virtual void Initialize() = 0;

	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	//状態に入った時
	virtual void Enter() = 0;
	//状態を抜けた時
	virtual void Exit() = 0;


	virtual void ResetGravity() = 0;

};

#endif		// IBOOMERANGSTATE_DEFINED
