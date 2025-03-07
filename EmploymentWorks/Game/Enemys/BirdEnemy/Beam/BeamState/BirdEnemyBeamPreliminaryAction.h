/*
	���̓G�̃r�[���̗���
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;
class BirdEnemyBeam;

//�\������N���X

// BirdEnemyBeamPreliminaryAction�N���X���`����
class BirdEnemyBeamPreliminaryAction : public IState
{
public:
	// �R���X�g���N�^
	BirdEnemyBeamPreliminaryAction(Player* player, BirdEnemy* birdEnemy, BirdEnemyBeam* beam);
	// �f�X�g���N�^
	~BirdEnemyBeamPreliminaryAction();
	// ����������
	void Initialize(CommonResources* resoure);

	// �X�V����
	void Update(const float& elapsedTime);
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	void Enter();
	void Exit();


private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	BirdEnemy* m_birdEnemy;


	Player* m_player;


	BirdEnemyBeam* m_beam;

	float m_time;

};

