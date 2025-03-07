/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "Game/Interface/IState.h"

class Player;
class Boomerang;

class BoomerangIdle : public IState
{
public:



public:
	//コンストラクタ
	BoomerangIdle() ;
	//デストラクタ
	~BoomerangIdle() override;


	//初期化
	void Initialize(CommonResources* resources) override;
	// 更新する
	void Update(const float& elapsedTime) override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;
	//必要なポインタの登録
	void AddPointer(Player* player, Boomerang* boomerang);

public:
	// 共通リソース
	CommonResources* m_commonResources;
	//ブーメラン
	Boomerang* m_boomerang;

	Player* m_player;

private :

	
};