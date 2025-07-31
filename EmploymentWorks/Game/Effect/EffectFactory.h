/*
	�N���X��     : EffectFactory
	����         : �G�t�F�N�g�̍쐬�E�Ǘ����s���N���X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Explosiion;
class BossChargeEffect;
class Particle;

class EffectFactory : public Actor
{
public:
	//�R���X�g���N
	EffectFactory(Scene* scene);
	//�f�X�g���N�^
	~EffectFactory() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);


private:
	//�����G�t�F�N�g
	std::vector<Explosiion*> m_explosiions;
	//�W���[�W�G�t�F�N�g
	std::vector<BossChargeEffect*> m_chargeEffects;
	//�p�[�e�B�N���G�t�F�N�g
	std::vector<Particle*> m_particles;

};