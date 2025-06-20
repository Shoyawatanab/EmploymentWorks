/*
	@file	BossBeam.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;
class BossBeamEnergyBall;
class BossBeamRays;
class BossBeamStateMachine;
class Player;
class BossEnemy;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossBeam : public Actor
{
public:

	//�`���[�W�G�t�F�N�g�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 EFFECT_SCALE{ 0.1f,0.1f,0.1f };

public:

	//�r�[���̎擾
	BossBeamEnergyBall* GetBossBeamEnergyBall() { return m_energyBall.get(); }
	//�����̎擾
	BossBeamRays* GetBossBeamRays() { return m_rays.get(); }



public:
	//�R���X�g���N
	BossBeam(Scene* scene);
	//�f�X�g���N�^
	~BossBeam() override;


	//������
	void Initialize() override;
	//�X�V����
	void  UpdateActor(const float& deltatime) override;




private:
	//�G�l���M�[�e
	std::unique_ptr<BossBeamEnergyBall> m_energyBall;
	//�\�����쎞��
	float m_preliminaryActitonTime;
	//����
	std::unique_ptr<BossBeamRays> m_rays;
	//�v���C��
	Player* m_player;

};
