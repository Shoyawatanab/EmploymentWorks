/*
	@file	Beam.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/CollisiionManager.h"
#include "Game/Interface/IStateMachine.h"
#include "Game/Entities/BaseEntity.h"

// �O���錾
class CommonResources;
class BeamEnergyBall;
class BeamChargeEffect;
class BeamRays;
class BeamStateMachine;
class Player;
class BossEnemy;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Beam : public BaseEntity
{
public:

	//�`���[�W�G�t�F�N�g�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 EFFECT_SCALE{ 0.1f,0.1f,0.1f };

public:

	//�r�[���̎擾
	BeamEnergyBall* GetBeamEnergyBall() { return m_energyBall.get(); }
	//�G�t�F�N�g�̎擾
	std::vector<std::unique_ptr< BeamChargeEffect>>&  GetBeamChargeEffect() { return m_chargeEffect; }
	//�����̎擾
	BeamRays* GetBeamRays() { return m_rays.get(); }



public:
	//�R���X�g���N
	Beam(CommonResources* resources);
	//�f�X�g���N�^
	~Beam() override;


	//������
	void Initialize() override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

	//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
	void AddPointer(BossEnemy* bossEnemy,Player* player);

	//�����蔻��̒ǉ�
	void AddCollionManager(CollisionManager* collsionManager) ;
	//�p�[�e�B�N������
	void CreateParticle();
	//�p�[�e�B�N���̍폜
	void RegistrationDeleteParticle(BeamChargeEffect* effect);



private:
	//�G�l���M�[�e
	std::unique_ptr<BeamEnergyBall> m_energyBall;
	//�\�����쎞��
	float m_preliminaryActitonTime;
	//�`���[�W�G�t�F�N�g
	std::vector<std::unique_ptr<BeamChargeEffect>> m_chargeEffect;
	//�폜����G�t�F�N�g
	std::vector<BeamChargeEffect*> m_deleteChargeEffect;
	//����
	std::unique_ptr<BeamRays> m_rays;
	//�v���C��
	Player* m_player;

};
