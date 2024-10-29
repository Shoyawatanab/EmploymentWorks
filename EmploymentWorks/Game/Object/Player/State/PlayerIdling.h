#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"
class CommonResources;

class Boomerang;
class Player;

// PlayerIdling�N���X���`����
class PlayerIdling : public IPlayerState
{
public:


	void ResetGravity() override;


	void SetResouces(CommonResources* resoure) { m_commonResources = resoure; }

public:
	// �R���X�g���N�^
	PlayerIdling();
	// �f�X�g���N�^
	~PlayerIdling();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(CommonResources* resoure, Player* player);


private:

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;



	Player* m_player;



	float m_graivty;


};

