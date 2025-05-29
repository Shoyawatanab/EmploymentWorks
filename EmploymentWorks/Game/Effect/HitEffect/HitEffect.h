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

	//エフェクトが有効かどうか
	const bool& GetIsActive() override { return m_isActive; };
	//エフェクトが有効かどうかの登録
	void SetIsActive(const bool& isActive) override { m_isActive = isActive; };
	//座標の登録
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override;
	//大きさの登録
	void SetScale(const DirectX::SimpleMath::Vector3& scale) override;
	//エフェクトの種類のタグ
	EffectType GetEffectType()  override { return EffectType::HIT_EFFECT; };



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

