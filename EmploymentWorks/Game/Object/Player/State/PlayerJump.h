#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"
class CommonResources;

class Boomerang;
class Player;

// PlayerJump�N���X���`����
class PlayerJump : public IPlayerState
{
public:


	void ResetGravity() override;



public:
	// �R���X�g���N�^
	PlayerJump();
	// �f�X�g���N�^
	~PlayerJump();
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





};
