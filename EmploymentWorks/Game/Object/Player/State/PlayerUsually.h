#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"
class CommonResources;

class Boomerang;
class Player;

// PlayerUsually�N���X���`����
class PlayerUsually : public IPlayerState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

	void SetResouces(CommonResources* resoure) { m_commonResources = resoure; }

public:
	// �R���X�g���N�^
	PlayerUsually();
	// �f�X�g���N�^
	~PlayerUsually();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(Player* player);


private:
	void Move(float elapsedTime,  DirectX::SimpleMath::Vector3 moveDirection);
	void Attack(float elapsedTime, DirectX::Keyboard::State key);
	void Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;



	Player* m_player;

	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;


	float m_graivty;

	DirectX::SimpleMath::Vector3 m_velocity;

};

