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

	DirectX::SimpleMath::Vector3 GetInitialScale() { return m_initialScale; }
	

	BeamEnergyBall* GetBeamEnergyBall() { return m_energyBall.get(); }

	std::vector<std::unique_ptr< BeamChargeEffect>>&  GetBeamChargeEffect() { return m_chargeEffect; }


	BeamRays* GetBeamRays() { return m_rays.get(); }



public:
	Beam(CommonResources* resources);


	//�f�X�g���N�^
	~Beam() override;

	//IObject
		//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

	//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
	void AddPointer(BossEnemy* bossEnemy,Player* player);


	void AddCollionManager(CollisionManager* collsionManager) ;

	void CreateParticle();

	void RegistrationDeleteParticle(BeamChargeEffect* effect);

	void DeleteParticle();

private:


	DirectX::SimpleMath::Vector3 m_initialScale;



	std::unique_ptr<BeamEnergyBall> m_energyBall;

	float m_preliminaryActitonTime;


	std::vector<std::unique_ptr<BeamChargeEffect>> m_chargeEffect;

	std::vector<BeamChargeEffect*> m_deleteChargeEffect;
	//����
	std::unique_ptr<BeamRays> m_rays;


	Player* m_player;

};
