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
	//�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


public:
	//�^�[�Q�b�g�̎擾
	const DirectX::SimpleMath::Vector3& GetTarget() { return m_target; }
	//�^�[�Q�b�g�̓o�^
	void SetTarget(const DirectX::SimpleMath::Vector3& target) { m_target = target; }
	//�X�e�[�g�}�V�[���̎擾
	BirdEnemyBeamStateMachine* GetStateMahine() { return m_stateMachine.get(); }
	//
	BirdEnemyBeamEnergyBall* GetBeamEnergyBall() { return m_energyBall.get(); }

public:
	//�R���X�g���N�^
	BirdEnemyBeam(CommonResources* resources, BirdEnemy* enemy);
	//�f�X�g���N�^
	~BirdEnemyBeam() override;	
	//������
	void Initialize() override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

	void UpdateBirdEnemyBeamPosition();
	//�R���W�����ɒǉ�
	void  AddCollision(CollisionManager* collsionManager);

private:

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;
	//�^�[�Q�b�g
	DirectX::SimpleMath::Vector3 m_target;
	//���̓G
	BirdEnemy* m_enemy;
	//�v���C��
	Player* m_player;
	//�G�l���M�[�e
	std::unique_ptr<BirdEnemyBeamEnergyBall> m_energyBall;
	//�X�e�[�g�}�V�[��
	std::unique_ptr<BirdEnemyBeamStateMachine> m_stateMachine;

};
