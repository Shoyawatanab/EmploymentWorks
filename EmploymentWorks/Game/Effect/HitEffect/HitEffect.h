/*
	ヒットエフェクトクラス
*/
#pragma once

#include "Game/Interface/IEffect.h"

class CommonResources;
class CircleParticle;

class HitEffect : public IEffect
{


public:


	bool GetIsActive() override { return m_isActive; };

	void SetIsActive(bool isActive) override { m_isActive = isActive; };

	EffectType GetEffectType()  override { return EffectType::HitEffect; };

	void SetPosition(DirectX::SimpleMath::Vector3 position) override;

	void SetScale(DirectX::SimpleMath::Vector3 scale) override;


public:
	// コンストラクタ
	HitEffect(CommonResources* resources);
	//デストラクタ
	~HitEffect() override;
	//初期化
	void Initialize() override;
	//更新
	void Update(const float& elapsedTime) override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;

	// 終了処理
	void Finalize();

	void Create(void* datas) override;

private:
	//共通リソース
	CommonResources* m_commonResources;
	//経過時間
	float m_time;
	bool m_isActive;

	//
	std::unique_ptr<CircleParticle> m_circleHitEffect;



};

