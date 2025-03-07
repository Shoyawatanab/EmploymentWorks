/*
	@file	BirdEnemyBeam.h
	@brief	���̓G�̃r�[��
*/
#pragma once
#include "Game/Enemys/BirdEnemy/Beam/BeamState/BirdEnemyBeamStateMachine.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeamEnergyBall.h"

#include "Game/Entities/BaseEntity.h"
// �O���錾
class CommonResources;
class BirdEnemy;
class Player;
class CollisionManager;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BirdEnemyBeam : public BaseEntity
{

public:
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


public:

	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }
 
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }
	

	BirdEnemyBeamStateMachine* GetStateMahine() { return m_stateMachine.get(); }

	BirdEnemyBeamEnergyBall* GetBeamEnergyBall() { return m_energyBall.get(); }

public:
	BirdEnemyBeam(CommonResources* resources, Player* player, BirdEnemy* enemy);

	//�f�X�g���N�^
	~BirdEnemyBeam() override;

	//IObject
		//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

	void UpdateBirdEnemyBeamPosition();

	void  AddCollision(CollisionManager* collsionManager);

private:



	// ���f��
	std::unique_ptr<DirectX::Model> m_model;
	DirectX::SimpleMath::Vector3 m_target;

	BirdEnemy* m_enemy;
	Player* m_player;
	std::unique_ptr<BirdEnemyBeamEnergyBall> m_energyBall;
	std::unique_ptr<BirdEnemyBeamStateMachine> m_stateMachine;

};
