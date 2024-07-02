#pragma once
/*
	@file	Player.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"

// �O���錾
class CommonResources;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Player final 

{
public:

	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	Boomerang* GetBoomerang() { return m_boomerang.get(); }

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_rotate;
	DirectX::SimpleMath::Vector3 m_direction; // �������Ă������

	std::unique_ptr<Boomerang> m_boomerang;

	Enemy* m_enemy;


public:
	Player(Enemy* enemy);
	~Player() ;

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position) ;
	void Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

private:
	void Move(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);
	void Attack(float elapsedTime, DirectX::Keyboard::State key);
	void Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);
};
