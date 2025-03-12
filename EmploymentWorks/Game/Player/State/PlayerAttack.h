/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "Game/Interface/IState.h"
#include "Game/Interface/IObserver.h"

class Player;

class PlayerAttack : public IState , IObserver
{
public:

	enum class ThrowState
	{
		Right = 0
		,Front
		, Left

	};

public:
	//コンストラクタ
	PlayerAttack() ;
	//デストラクタ
	~PlayerAttack() override;

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

	//通知時に呼び出される
	void Notify(EventParams::EventType type, void* datas) override;


	//必要なポインタの登録
	void AddPointer(Player* player);


private:
	// 共通リソース
	CommonResources* m_commonResources;
	//
	Player* m_player;
	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;
	//回転
	DirectX::SimpleMath::Quaternion m_rotation;
	
	ThrowState m_throwState;

};