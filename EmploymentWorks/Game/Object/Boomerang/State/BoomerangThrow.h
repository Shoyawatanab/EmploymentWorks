#pragma once
#include <pch.h>
#include "Interface/IBoomerangState.h"
#include "Libraries/MyLib/CSV.h"

class Boomerang;
class Player;

// BoomerangThrowクラスを定義する
class BoomerangThrow : public IBoomerangState
{
public: 
	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

	std::vector<DirectX::SimpleMath::Vector3> GetSS() { return m_spherePos; }

public:
	// コンストラクタ
	BoomerangThrow(Boomerang* boomerang, Player* player);
	// デストラクタ
	~BoomerangThrow();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	void SplineCurve(const float& elapsedTime);

private:

	Boomerang* m_boomerang;
	Player* m_player;

	DirectX::SimpleMath::Quaternion m_rotate;
	DirectX::SimpleMath::Vector3 m_position;

	std::unique_ptr<CSV> m_csv;

	std::vector<DirectX::SimpleMath::Vector3> m_spherePos;
	std::vector<DirectX::SimpleMath::Vector3> m_moveSpherePos;

	// デバイスコンテキスト
	ID3D11DeviceContext* m_context;
	// ワールドマトリックス
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// バウンディングスフィア
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

	float m_transformRatio;
	int m_index;
	float m_totalTime;
	int m_startIndex;

	float m_moveSpeed;


};

