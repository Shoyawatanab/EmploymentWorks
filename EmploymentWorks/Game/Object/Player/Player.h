#pragma once
/*
	@file	Player.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Interface/ICollisionObject.h"

#include "Interface/IPlayerState.h"
#include "Game/Object/Player/State/PlayerUsually.h"
#include "Game/Object/Player/State/PlayerBlownAway.h"

// �O���錾
class CommonResources;
class Bounding;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Player : public ICollisionObject

{
public:

	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }

	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_rotate = rotate; }
	Boomerang* GetBoomerang() { return m_boomerang.get(); }

	bool GetIsLockOn() { return m_isLockOn; }
	void SetisLockOn(bool isLockOn) { m_isLockOn = isLockOn; }

	DirectX::SimpleMath::Vector3 GetPlayerForWard() { return m_direction; }
	void SetPlayerForWard(DirectX::SimpleMath::Vector3 direction) { m_direction = direction; }

	void SetCameraRotate(DirectX::SimpleMath::Quaternion rotate) { m_cameraRatate = rotate; }
	DirectX::SimpleMath::Quaternion GetCameraRotate() { return m_cameraRatate; }

	int GetPlayerHP() { return m_hp; }
	void SetPlayerHP(int hp) { m_hp = hp; }

	DirectX::SimpleMath::Vector3 GetBlownAwayDirection() { return m_blownAwayDirection; }

	//State�֌W
	IPlayerState* GetPlayerState() { return m_currentState; }
	PlayerUsually* GetPlayerUsually() { return m_usually.get(); }
	PlayerBlownAway* GetPlayerBlownAway() { return m_blownAway.get(); }

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_rotate;
	DirectX::SimpleMath::Vector3 m_direction; // �������Ă������

	//���ł�����
	DirectX::SimpleMath::Vector3 m_blownAwayDirection;

	std::unique_ptr<Boomerang> m_boomerang;

	Enemy* m_enemy;
	std::unique_ptr<Bounding> m_bounding;

	float m_graivty;

	bool m_isLockOn;

	float m_hp;

	DirectX::SimpleMath::Quaternion m_cameraRatate;

	//State�֌W
	IPlayerState* m_currentState;
	std::unique_ptr<PlayerUsually> m_usually;
	std::unique_ptr<PlayerBlownAway> m_blownAway;

public:
	Player(Enemy* enemy);
	~Player() ;

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position);
	void Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

	void ChangeState(IPlayerState* nextState);

	void DemandBlownAwayDirection(DirectX::SimpleMath::Vector3 pos);


	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Player; }

	void SetPos(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPos() override { return m_position; }

	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

};