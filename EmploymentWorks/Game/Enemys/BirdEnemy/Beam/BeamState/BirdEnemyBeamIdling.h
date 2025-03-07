/*
	���̓G�̃r�[���̒ʏ���
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;
class BirdEnemyBeam;

// BirdEnemyBeamIdling�N���X���`����
class BirdEnemyBeamIdling : public IState
{
public:
	// �R���X�g���N�^
	BirdEnemyBeamIdling(Player* player, BirdEnemy* birdEnemy, BirdEnemyBeam* beam);
	// �f�X�g���N�^
	~BirdEnemyBeamIdling();
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

};

