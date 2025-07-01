#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Explosiion;
class BossChargeEffect;
class Particle;

class EffectFactory : public Actor , public IObserver<SceneMessageType>
{
public:
	//�R���X�g���N
	EffectFactory(Scene* scene);
	//�f�X�g���N�^
	~EffectFactory() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas)  override;


private:
	//�����G�t�F�N�g
	std::vector<Explosiion*> m_explosiions;
	//�W���[�W�G�t�F�N�g
	std::vector<BossChargeEffect*> m_chargeEffects;
	//�p�[�e�B�N���G�t�F�N�g
	std::vector<Particle*> m_particles;

};