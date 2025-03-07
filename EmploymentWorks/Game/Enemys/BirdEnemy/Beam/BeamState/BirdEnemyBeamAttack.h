/*
	���̓G�̃r�[���̍U��
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;
class BirdEnemyBeam;

// BirdEnemyBeamAttack�N���X���`����
class BirdEnemyBeamAttack : public IState
{
public:
	// �R���X�g���N�^
	BirdEnemyBeamAttack(Player* player, BirdEnemy* birdEnemy, BirdEnemyBeam* beam);
	// �f�X�g���N�^
	~BirdEnemyBeamAttack();
	// ����������
	void Initialize(CommonResources* resoure);

	// �X�V����
	void Update(const float& elapsedTime);
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;

	void Enter();
	void Exit();


	float Lerp(float start, float end, float t);

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//���̓G
	BirdEnemy* m_birdEnemy;
	//�v���C��
	Player* m_player;
	//�r�[��
	BirdEnemyBeam* m_beam;
	//��������
	DirectX::SimpleMath::Vector3 m_moveDirectiion;
	//�����̃X�s�[�h
	float m_initialSpeed;
	//�ŏI�X�s�[�h
	float m_finalSpeed;
	//��������
	float m_decelerationTime;
	//����
	float m_time;

};


