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




public:
	BarrierGenerate(CommonResources* resources
	, Barrier* barrier);
	
	//デストラクタ
	~BarrierGenerate() ;

	//初期化
	void Initialize(CommonResources* resources) ;
	// 更新する
	void Update(const float& elapsedTime);
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	//状態に入った時
	void Enter();
	//状態を抜けた時
	void Exit() ;

private:

	Barrier* m_barrier;

	float m_time;




};
