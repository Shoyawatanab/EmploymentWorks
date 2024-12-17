#pragma once
#ifndef IBIRD_DEFINED
#define IBIRD_DEFINED

// IBoomerangStateインタフェースを定義する(GOF Stateパターン)
class IBirdEnemyState
{
public:
	virtual ~IBirdEnemyState() = default;
	// 初期化する
	virtual void Initialize() = 0;

	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	//状態に入った時
	virtual void Enter() = 0;
	//状態を抜けた時
	virtual void Exit() = 0;



};

#endif		// IBOOMERANGSTATE_DEFINED
