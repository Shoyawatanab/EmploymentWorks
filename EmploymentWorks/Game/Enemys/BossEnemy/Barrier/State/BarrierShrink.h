/*
	@file	BarrierShrink.h
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

class BarrierShrink : public IState
{
public:
	//コンストラク
	BarrierShrink(CommonResources* resources
	, Barrier* barrier);
	
	//デストラクタ
	~BarrierShrink() ;

	//初期化
	void Initialize(CommonResources* resources) ;
	// 更新処理
	void Update(const float& elapsedTime);
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
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
