/*
* カメラのStateのインターフェース
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IState.h"


class ICamera : public IState
{
public:
	//デストラクタ
	virtual ~ICamera() = default;
	////初期化
	//virtual void Initialize() = 0;
	//// 更新する
	//virtual void Update(const float& elapsedTime) = 0;
	////状態に入った時
	//virtual void Enter() = 0;
	////状態を抜けた時
	//virtual void Exit() = 0;
	//Matrixの取得
	virtual const DirectX::SimpleMath::Matrix& GetViewMatrix() = 0;

};
