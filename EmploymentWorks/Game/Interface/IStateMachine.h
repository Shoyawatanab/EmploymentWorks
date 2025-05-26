/*
* ステーとパターンのインターフェース
*/
#pragma once
#include "pch.h"

class IState;
class CommonResources;


class IStateMachine
{
public:
	//デストラクタ
	virtual ~IStateMachine() = default;
	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	//描画
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) = 0;
	//状態の変更
	virtual void ChangeState(IState* nextState) = 0;

};
