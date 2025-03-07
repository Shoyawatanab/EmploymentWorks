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

class EffectsManager : public IObserver

{
public:
	EffectsManager();
	~EffectsManager() ;

	void Initialize(CommonResources* resources);
	//更新処理
	void Update(const float& elapsedTime);
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	void Finalize() ;

	void CreateExploion(void* datas);

	void CreatePlayerDamageEffect(void* datas);
	void CreateParticle(void* datas);

	void CreateHitEffect(void* datas);

	void Notify(EventParams::EventType type, void* datas)  override;


private:
	// 共通リソース
	CommonResources* m_commonResources;

	std::vector<std::unique_ptr<IEffect>> m_effects;



};
