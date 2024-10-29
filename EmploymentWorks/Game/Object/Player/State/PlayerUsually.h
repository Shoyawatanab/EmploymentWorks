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


	void ResetGravity() override;

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
	void RegistrationInformation(CommonResources* resoure,Player* player);


private:
	void Move(float elapsedTime,  DirectX::SimpleMath::Vector3 moveDirection);
	void Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;



	Player* m_player;



	float m_graivty;


};

