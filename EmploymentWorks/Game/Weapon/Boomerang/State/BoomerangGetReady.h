/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "Game/Interface/IState.h"

class Boomerang;

class BoomerangGetReady : public IState
{
public:



public:
	//コンストラクタ
	BoomerangGetReady(Boomerang* boomerang) ;
	//デストラクタ
	~BoomerangGetReady() override;

	//初期化
	void Initialize(CommonResources* resources) ;
	// 更新する
	void Update(const float& elapsedTime) override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

public:
	// 共通リソース
	CommonResources* m_commonResources;
	//ブーメラン
	Boomerang* m_boomerang;



private :
	
};