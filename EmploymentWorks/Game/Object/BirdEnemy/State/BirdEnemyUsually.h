#pragma once
#include <pch.h>
#include "Interface/IBirdEnemyState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyUsually�N���X���`����
class BirdEnemyUsually : public IBirdEnemyState
{
public:



	void SetResouces(CommonResources* resoure) { m_commonResources = resoure; }

public:
	// �R���X�g���N�^
	BirdEnemyUsually();
	// �f�X�g���N�^
	~BirdEnemyUsually();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(CommonResources* resoure,Player* player,BirdEnemy* birdEnemy);


private:
	void Move(float elapsedTime,  DirectX::SimpleMath::Vector3 moveDirection);
	void Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	BirdEnemy* m_birdEnemy;

	Player* m_player;





};

