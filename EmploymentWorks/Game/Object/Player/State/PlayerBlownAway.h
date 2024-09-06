#pragma once
#include <pch.h>
#include "Interface/IPlayerState.h"

class Boomerang;
class Player;

// PlayerBlownAway�N���X���`����
class PlayerBlownAway : public IPlayerState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	PlayerBlownAway(Boomerang* boomerang , Player* player);
	// �f�X�g���N�^
	~PlayerBlownAway();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();


private:
	Boomerang* m_boomerang;

	Player* m_player;

	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;

	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector3 m_direction;


	float m_graivty;



};

