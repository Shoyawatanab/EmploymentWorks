#pragma once
/*
	@file	Player.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/PlayerParts/PlayerBase.h"

#include "Interface/IPlayerState.h"
#include "Game/Object/Player/State/PlayerUsually.h"
#include "Game/Object/Player/State/PlayerBlownAway.h"
#include "Game/Object/Player/State/PlayerAttack.h"
#include "Game/Object/Player/State/PlayerJump.h"
#include "Game/Object/Player/State/PlayerIdling.h"

// �O���錾
class CommonResources;
class Bounding;
class PlayScene;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
	class TPS_Camera;

}


class Player : public PlayerBase

{
public:



	//DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	//void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_rotate = rotate; }
	Boomerang* GetUsingBoomerang() { return m_boomerang[m_boomerangIndex].get(); }

	bool GetIsLockOn() { return m_isLockOn; }
	void SetisLockOn(bool isLockOn) { m_isLockOn = isLockOn; }

	DirectX::SimpleMath::Vector3 GetPlayerForWard() { return m_direction; }
	void SetPlayerForWard(DirectX::SimpleMath::Vector3 direction) { m_direction = direction; }

	void SetCameraRotate(DirectX::SimpleMath::Quaternion rotate) { m_cameraRatate = rotate; }
	DirectX::SimpleMath::Quaternion GetCameraRotate() { return m_cameraRatate; }

	float GetPlayerHP() { return m_hp; }
	void SetPlayerHP(float hp) { m_hp = hp; }

	DirectX::SimpleMath::Vector3 GetBlownAwayDirection() { return m_blownAwayDirection; }

	//
	DirectX::SimpleMath::Vector3 GetPlayerEyePosition() { return m_eyePosition; }
	void SetPlayerEyePosition(DirectX::SimpleMath::Vector3 eyePosition) {  m_eyePosition = eyePosition; }

	//State�֌W
	IPlayerState* GetPlayerState() { return m_currentState; }
	PlayerUsually* GetPlayerUsually() { return m_usually.get(); }
	PlayerBlownAway* GetPlayerBlownAway() { return m_blownAway.get(); }
	PlayerAttack* GetPlayerAttack() { return m_attack.get(); }
	PlayerJump* GetPlayerJump() { return m_jump.get(); }
	PlayerIdling* GetPlayerIding() { return m_idling.get(); }

	//�g�p���̃u�[��������Index�̎擾
	int GetUsingBoomerangIndex() { return m_boomerangIndex; }

	void SetIsJump(bool isjump) { m_isJump = isjump; }
	bool GetisJump() { return m_isJump; }

	mylib::TPS_Camera* GetTPS_Camera() { return m_tpsCamera; }

	int GetBoomerangIndex() { return m_boomerangIndex; }

	DirectX::SimpleMath::Vector3 InitialRotate() { return m_initialRotate; }

	DirectX::SimpleMath::Vector3 GetVelocity() { return m_velocity; }

	void SetVelocity(DirectX::SimpleMath::Vector3 velocity) { m_velocity = velocity; }


	void SetIsInvincible(bool is) { m_isInvincible = is; }

	bool GetIsInvincible() { return m_isInvincible; }

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;


	// �X�N���[���z�C�[���l
	int m_scrollWheelValue;

	//�Q�[���J���� �v���C���̃J����
	mylib::TPS_Camera* m_tpsCamera;



	DirectX::SimpleMath::Vector3 m_scale;
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_rotate;
	DirectX::SimpleMath::Vector3 m_initialRotate;
	DirectX::SimpleMath::Vector3 m_direction; // �������Ă������

	//�ڂ̍��W
	DirectX::SimpleMath::Vector3 m_eyePosition;

	//���ł�����
	DirectX::SimpleMath::Vector3 m_blownAwayDirection;

	//�g�p���Ă���
	//Boomerang* m_usingBoomerang;
	int m_boomerangIndex;

	//�u�[������
	std::vector<std::unique_ptr<Boomerang>> m_boomerang;

	Enemy* m_enemy;
	std::unique_ptr<Bounding> m_bounding;

	float m_graivty;

	DirectX::SimpleMath::Vector3 m_velocity;

	bool m_isLockOn;

	bool m_isJump;

	float m_hp;

	DirectX::SimpleMath::Quaternion m_cameraRatate;

	std::unique_ptr<PlayerUsually>    m_usually;

	//State�֌W
	IPlayerState* m_currentState;
	std::unique_ptr<PlayerIdling>    m_idling;
	std::unique_ptr<PlayerBlownAway>  m_blownAway;
	std::unique_ptr<PlayerAttack>     m_attack;
	std::unique_ptr<PlayerJump>       m_jump;

	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	//���G���ǂ���
	bool m_isInvincible;
	float m_invincibleTime;
	//�_�Ł@true �\���@false ��펞
	bool m_isVisible;

public:
	Player(CommonResources* resources, IComponent* parent, const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);
	~Player() ;

	void Initialize();
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) ;
	void Finalize() ;

	void ChangeState(IPlayerState* nextState);

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(Enemy* enemy,mylib::TPS_Camera* tps_Camera,PlayScene* playScene);

	//�N���X�̃C���X�^���X
	void Instances();

	void DemandBlownAwayDirection(DirectX::SimpleMath::Vector3 pos);


	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Player; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition() override { return m_position; }

	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

	//���݂̑傫���̎擾
	DirectX::SimpleMath::Vector3 GetScale() const override { return m_scale; }
	// ���݂̉�]�p���擾����
	DirectX::SimpleMath::Quaternion GetAngle() const override { return m_rotate; }
	// ���݂̉�]�p��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) override { m_rotate = currentAngle; }


};
