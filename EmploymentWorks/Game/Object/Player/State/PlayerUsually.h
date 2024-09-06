#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"

class Boomerang;
class Player;

// PlayerUsually�N���X���`����
class PlayerUsually : public IPlayerState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	PlayerUsually(Boomerang* boomerang , Player* player);
	// �f�X�g���N�^
	~PlayerUsually();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();


private:
	void Move(float elapsedTime,  DirectX::SimpleMath::Vector3 moveDirection);
	void Attack(float elapsedTime, DirectX::Keyboard::State key);
	void Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);

private:
	Boomerang* m_boomerang;

	Player* m_player;

	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;


	float m_graivty;



};

