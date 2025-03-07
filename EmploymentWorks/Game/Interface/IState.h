/*
* ステーとパターンのインターフェース
*/
#pragma once
#include "pch.h"

class CommonResources;


class IState
{
public:
	//デストラクタ
	virtual ~IState() = default;
	//初期化
	virtual void Initialize(CommonResources* resources) = 0;
	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	//描画
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) = 0;
	//状態に入った時
	virtual void Enter() = 0;
	//状態を抜けた時
	virtual void Exit() = 0;



};
