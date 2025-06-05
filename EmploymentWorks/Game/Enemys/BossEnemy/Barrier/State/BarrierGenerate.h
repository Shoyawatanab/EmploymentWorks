/*
	@file	BarrierGenerate.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IState.h"

// 前方宣言
class CommonResources;
class Barrier;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class Bounding;

}

class BarrierGenerate : public IState
{

public:
	//コンストラク
	BarrierGenerate(CommonResources* resources
	, Barrier* barrier);
	
	//デストラクタ
	~BarrierGenerate() ;

	//初期化
	void Initialize(CommonResources* resources) ;
	// 更新処理
	void Update(const float& elapsedTime);
	//状態に入った時
	void Enter();
	//状態を抜けた時
	void Exit() ;

private:
	//バリア
	Barrier* m_barrier;
	//時間
	float m_time;




};
