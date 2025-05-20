#pragma once
/*
	@file	EffectsManager.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IEffect.h"
#include "Game/Interface/IObserver.h"

// 前方宣言
class CommonResources;

class EffectsManager : public IObserver<GameMessageType>
{
public:

	//爆発エフェクトの数
	static constexpr int EXPLOION_EFFECT_COUNT = 10;
	//パーティクルエフェクトの数
	static constexpr int PARTICLE_EFFECT_COUNT = 2;
	//ヒットエフェクトの数
	static constexpr int HIT_EFFECT_COUNT = 30;
public:
	//コンストラクタ
	EffectsManager();
	//デストラクタ
	~EffectsManager() ;
	//初期化
	void Initialize(CommonResources* resources);
	//更新処理
	void Update(const float& elapsedTime);
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	//
	void Finalize() ;

private:
	//爆発エフェクトの生成
	void CreateExploion(void* datas);
	//プレイヤダメージ絵エフェクトの生成
	void CreatePlayerDamageEffect(void* datas);
	//パーティクルエフェクトの生成
	void CreateParticle(void* datas);
	//ヒットエフェクトの生成
	void CreateHitEffect(void* datas);
	//チャージエフェクトの生成
	void CreateChargeEffect(void* datas);
	//通知
	void Notify(const Telegram<GameMessageType>& telegram)  override;
	//エフェクトの作成
	void CreateEffect();

private:
	// 共通リソース
	CommonResources* m_commonResources;
	//エフェクトをまとめる変数
	std::vector<std::unique_ptr<IEffect>> m_effects;



};
