/*
	ヒットエフェクトクラス
*/
#pragma once
#include "Game/Interface/IEffect.h"

//前方宣言
class CommonResources;
class CircleParticle;

class HitEffect : public IEffect
{


public:

	//オブジェクトが有効かどうか
	bool GetIsActive() override { return m_isActive; };
	//オブジェクトが有効かどうかの登録
	void SetIsActive(bool isActive) override { m_isActive = isActive; };
	//エフェクトの種類のタグ
	EffectType GetEffectType()  override { return EffectType::HIT_EFFECT; };
	//座標の登録
	void SetPosition(DirectX::SimpleMath::Vector3 position) override;
	//大きさの登録
	void SetScale(DirectX::SimpleMath::Vector3 scale) override;


public:
	// コンストラクタ
	HitEffect(CommonResources* resources);
	//デストラクタ
	~HitEffect() override;
	//初期化
	void Initialize() override;
	//更新処理
	void Update(const float& elapsedTime) override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const  DirectX::SimpleMath::Matrix& proj) override;

	// 終了処理
	void Finalize();

private:
	//エフェクトの作成
	void Create(void* datas) override;

private:
	//共通リソース
	CommonResources* m_commonResources;
	//経過時間
	float m_time;
	//オブジェクトが有効か
	bool m_isActive;

	//円のエフェクトクラス
	std::unique_ptr<CircleParticle> m_circleHitEffect;



};

