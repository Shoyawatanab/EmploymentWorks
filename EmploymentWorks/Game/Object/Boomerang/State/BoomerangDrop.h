#pragma once
#include <pch.h>
#include "Interface/IBoomerangState.h"

class Boomerang;

// BoomerangDropクラスを定義する
class BoomerangDrop : public IBoomerangState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// コンストラクタ
	BoomerangDrop();
	// デストラクタ
	~BoomerangDrop();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(Boomerang* boomerang);


private:
	Boomerang* m_boomerang;


	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;

};

