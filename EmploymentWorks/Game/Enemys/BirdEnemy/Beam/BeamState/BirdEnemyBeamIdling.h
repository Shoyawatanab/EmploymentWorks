/*
	���̓G�̃r�[���̒ʏ���
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"

//�O���錾
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
	//��Ԃɓ�������
	void Enter();
	//��Ԃ𔲂�����
	void Exit();


private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//���̓G
	BirdEnemy* m_birdEnemy;
	//�v���C��
	Player* m_player;
	//�r�[��
	BirdEnemyBeam* m_beam;

};

