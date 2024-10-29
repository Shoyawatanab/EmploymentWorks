#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"
class CommonResources;

class Boomerang;
class Player;

// PlayerBlownAway�N���X���`����
class PlayerBlownAway : public IPlayerState
{
public:


	void ResetGravity() override;


public:
	// �R���X�g���N�^
	PlayerBlownAway();
	// �f�X�g���N�^
	~PlayerBlownAway();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(CommonResources* resoure, Player* player);


private:
	CommonResources* m_commonResources;



	Player* m_player;


	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector3 m_direction;


	float m_graivty;



};

