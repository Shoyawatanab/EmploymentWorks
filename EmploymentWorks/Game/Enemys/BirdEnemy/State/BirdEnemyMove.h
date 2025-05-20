/*
�@���̓G�̓���
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"
//�O���錾
class CommonResources;
class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyMove�N���X���`����
class BirdEnemyMove : public IState
{

public:
	// �R���X�g���N�^
	BirdEnemyMove();
	// �f�X�g���N�^
	~BirdEnemyMove();
	// ������
	void Initialize(CommonResources* resoure);

	// �X�V����
	void Update(const float& elapsedTime);

	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	//��Ԃɓ�������
	void Enter();
	//��Ԃ𔲂�����
	void Exit();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void AddPointer(Player* player, BirdEnemy* birdEnemy);

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//���̓G
	BirdEnemy* m_birdEnemy;
	//�v���C��
	Player* m_player;
	//���߂̍��W
	DirectX::SimpleMath::Vector3 m_startPosition;
	//�I���̍��W
	DirectX::SimpleMath::Vector3 m_endPosition;
	//����
	float m_time;



};

