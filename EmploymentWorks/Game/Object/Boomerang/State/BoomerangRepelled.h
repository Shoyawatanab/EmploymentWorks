//弾かれる処理

#pragma once
#include <pch.h>
#include "Interface/IBoomerangState.h"

class Boomerang;

// BoomerangRepelledクラスを定義する
class BoomerangRepelled : public IBoomerangState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// コンストラクタ
	BoomerangRepelled(Boomerang* boomerang);
	// デストラクタ
	~BoomerangRepelled();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

private:
	Boomerang* m_boomerang;

	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;

	DirectX::SimpleMath::Vector3 m_direction;

	DirectX::SimpleMath::Vector3 m_position;

	float m_pwoer;

	float m_graivty;


};

