#pragma once
#include "GameBase/Actor.h"

class BossEnemyBeamEnergyBall;
class BossEnemyBeamRays;

class BossEnemyBeam : public Actor
{
public:
	//�e�̎擾
	BossEnemyBeamEnergyBall* GetEnergyBall() { return m_energyBall; }
	//�����̎擾
	BossEnemyBeamRays* GetRays() { return m_rays; }
public:
	//�R���X�g���N
	BossEnemyBeam(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyBeam();

private:
	//����
	BossEnemyBeamRays* m_rays;
	//�e
	BossEnemyBeamEnergyBall* m_energyBall;
	//�^�[�Q�b�g
	Actor* m_target;

};


