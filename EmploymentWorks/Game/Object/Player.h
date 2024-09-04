#pragma once
/*
	@file	Player.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Interface/ICollisionObject.h"

// 前方宣言
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
	Boomerang* GetBoomerang() { return m_boomerang.get(); }


	bool GetIsLockOn() { return m_isLockOn; }
	void SetisLockOn(bool isLockOn) { m_isLockOn = isLockOn; }

	DirectX::SimpleMath::Vector3 GetPlayerForWard() { return m_direction; }

	void SetCameraRotate(DirectX::SimpleMath::Quaternion rotate) { m_cameraRatate = rotate; }
	DirectX::SimpleMath::Quaternion m_cameraRatate;


private:
	// 共通リソース
	CommonResources* m_commonResources;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_rotate;
	DirectX::SimpleMath::Vector3 m_direction; // 今向いている方向

	std::unique_ptr<Boomerang> m_boomerang;

	Enemy* m_enemy;
	std::unique_ptr<Bounding> m_bounding;

	float m_graivty;

	bool m_isLockOn;



public:
	Player(Enemy* enemy);
	~Player() ;

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position);
	void Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;


	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Player; }

	void SetPos(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPos() override { return m_position; }

	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

private:
	void Move(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);
	void Attack(float elapsedTime, DirectX::Keyboard::State key);
	void Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);
};
