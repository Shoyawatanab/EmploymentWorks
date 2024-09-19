/*
	IBehaviorNode.h
	渡邊翔也
	ビヘイビアツリーの実行のみのノード
	子を持たない
*/
#pragma once
#include "pch.h"



class IBehaviorNode
{
public:

	enum class State
	{
		Success,         //成功
		Failure,      //失敗
		Runngin      //実行中
	};

public:
	virtual ~IBehaviorNode() = default;

	virtual void Initialize() = 0;

	virtual State Update(float elapsdTime) = 0;

	//実行中の時のUpdate
	virtual State RunningUpdate(float elapsdTime) = 0;

	virtual void Finalize() = 0;
};
