#pragma once
/*
	@file	EffectsManager.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IEffect.h"
#include "Game/Interface/IObserver.h"

// �O���錾
class CommonResources;

class EffectsManager : public IObserver

{
public:
	EffectsManager();
	~EffectsManager() ;

	void Initialize(CommonResources* resources);
	//�X�V����
	void Update(const float& elapsedTime);
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	void Finalize() ;

	void CreateExploion(void* datas);

	void CreatePlayerDamageEffect(void* datas);
	void CreateParticle(void* datas);

	void CreateHitEffect(void* datas);

	void Notify(EventParams::EventType type, void* datas)  override;


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	std::vector<std::unique_ptr<IEffect>> m_effects;



};
