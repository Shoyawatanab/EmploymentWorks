//弾かれる処理

#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"

class Boomerang;

// BoomerangRepelledクラスを定義する
class BoomerangRepelled : public IState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// コンストラクタ
	BoomerangRepelled(Boomerang* boomerang);
	// デストラクタ
	~BoomerangRepelled();
	//初期化
	void Initialize(CommonResources* resources) ;
	// 更新する
	void Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;



private:
	//ブーメラン
	Boomerang* m_boomerang;

	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
	//方向
	DirectX::SimpleMath::Vector3 m_direction;
	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//パワー
	float m_pwoer;
	//重力
	float m_graivty;


};

