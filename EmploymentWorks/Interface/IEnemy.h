#pragma once
#ifndef IEnemyState_DEFINED
#define IEnemyState_DEFINED

// IEnemyStateインタフェースを定義する(GOF Stateパターン)
class IEnemy
{
public:
	virtual ~IEnemy() = default;
	// 初期化する
	virtual void Initialize() = 0;

	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	//描画
	virtual void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj) = 0;

};

#endif		// IEnemyState_DEFINED
