#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"

class Boomerang;

// BoomerangDropクラスを定義する
class BoomerangDrop : public IState
{
public:

	//ワールド行列の取得
	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:

	// コンストラクタ
	BoomerangDrop(Boomerang* boomerang);
	// デストラクタ
	~BoomerangDrop();
	//初期化
	void Initialize(CommonResources* resources) ;
	// 更新する
	void Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;	//クラスに必要な情報（ポインタ）の登録

private:
	
	//ブーメラン
	Boomerang* m_boomerang;

	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;

};

