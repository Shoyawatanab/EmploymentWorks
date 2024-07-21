#pragma once
#ifndef ICameCamera_DEFINED
#define ICameCamera_DEFINED

// ICameCameraインタフェースを定義する(GOF Stateパターン)
class IGameCamera
{
public:

	// 初期化する
	virtual void Initialize() = 0;

	// 更新する
	virtual void Update(const float& elapsedTime) = 0;

	//状態に入った時
	virtual void Enter() = 0;
	//状態を抜けた時
	virtual void Exit() = 0;

	virtual const DirectX::SimpleMath::Matrix& GetViewMatrix() = 0;



};

#endif		// ICameCamera_DEFINED
