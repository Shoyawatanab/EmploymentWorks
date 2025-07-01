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

	void SetTarget(Actor* target) { m_target = target; }

public:
	//�R���X�g���N
	BossEnemyBeam(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyBeam();
	//�I�u�W�F�N�g�ʂ̍X�V����
	void UpdateActor(const float& deltaTime) override;

	//�^�[�Q�b�g�Ɍ����ĉ�]
	void TargetToRotation();

private:
	//����
	BossEnemyBeamRays* m_rays;
	//�e
	BossEnemyBeamEnergyBall* m_energyBall;
	//�^�[�Q�b�g
	Actor* m_target;

};


