#pragma once
/*
	@file	Enemy.h.h
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include"Game/Object/Boomerang/Boomerang.h"
#include "Interface/ICollisionObject.h"
#include "Interface/IBehaviorNode.h"

#include "Game/Object/Enemy/BossEnemy/BossEnemyBase.h"
#include "Libraries/MyLib/Animation.h"
#include "Libraries/MyLib/Shadow.h"

// �O���錾
class CommonResources;
class Bounding;
class BehaviorTree;
class Player;
class Beam;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Enemy : public BossEnemyBase
	
{
public:


	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_rotate = rotate; }
	// GetScale() { return m_scale; }

	DirectX::SimpleMath::Vector3 GetTargetPos() { return m_targetPos; }

	DirectX::SimpleMath::Vector3 Getforward() { return m_forward; }
	void Setforward(DirectX::SimpleMath::Vector3 direction) { m_forward = direction; }


	bool GetIsAttack() { return m_isAttack; }

	Beam* GetBeam() { return m_beam.get(); }

	DirectX::SimpleMath::Vector3 GetBeamStartPosition() { return m_beamStartPosition; }

public:

	//�����̃^�[�Q�b�g�̍��W�̋���
	static const DirectX::SimpleMath::Vector3 STAETTAEGETDIRECTION;

	//�G�̏����̌����Ă������
	static const DirectX::SimpleMath::Vector3 INITIALFORWARD;


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	// ���f��
	//std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_initialRotate;
	DirectX::SimpleMath::Quaternion m_rotate;

	std::unique_ptr<Bounding> m_bounding;

	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;


	float m_hp;
	float m_maxHP;
	float m_graivty;


	float m_collisionTime;
	bool m_isCollsionTime;

	DirectX::SimpleMath::Vector3 m_scale;


	std::unique_ptr<BehaviorTree> m_behavior;

	Player* m_player;

	//�����Ă������
	DirectX::SimpleMath::Vector3 m_forward;


	//�m�b�N�o�b�N�̕���
	DirectX::SimpleMath::Vector3 m_knockbackDirection;
	float m_acceleration;
	float m_knockbackTime;


	//�u�[�������̃^�[�Q�b�g�̍��W
	DirectX::SimpleMath::Vector3 m_targetPos;

	//�r�[���N���X
	std::unique_ptr<Beam> m_beam;


	//�����������̑���̃^�O
	CollsionObjectTag m_onCollisionTag;

	bool m_isAttack;

	DirectX::SimpleMath::Vector3 m_boundingBoxCenter;

	//�r�[���U���̃X�^�[�g���W
	DirectX::SimpleMath::Vector3 m_beamStartPosition;

	//�r�[�����E��őł��̓G�̒��S����̋���
	DirectX::SimpleMath::Vector3 m_rightHandPos;
	//�U���̗\�����쎞��
	float m_preliminaryActionTime;

	//Walk�Ɋւ���֐�
	float m_walkSpeed;
	float m_walkAccelration;
	float m_stepDuration;
	float m_stepTime;
	bool m_isStep;

	//�W�����v�֌W�֐�
	//�W�����v�̍��W�@�P�D�����l�@�Q�@���ԍ��W�@�R�ŏI���W�@�S�@�X�v���C���Ȑ��p�ɋ��߂�
	std::vector<DirectX::SimpleMath::Vector3> m_jumpPosition;
	//�W�����v�̍���
	float m_jumpHeight;
	//
	bool m_isJumpAttack;
	//�W�����v�U�����W�̃C���f�b�N�X
	int m_jumpAttackIndex;
	//�_�Ɠ_�̊Ԃ̈ړ�����
	float m_transformRatio;
	float m_jumpAttackTime;


	// �e�I�u�W�F�N�g
	std::unique_ptr<Shadow> m_shadow;


public:
	Enemy(CommonResources* resources, BossEnemyBase* parent,
		const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& initialPosition, 
		const DirectX::SimpleMath::Quaternion& initialAngle, int partsHp);
	~Enemy() ;

	void Initialize() ;
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) ;
	void Finalize() ;

	Animation::AnimationState FallDwonAnimation(float elapsdTime);

	void SetAnimation(std::string name);

	//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
	void RegistrationInformation(Player* player);

	//�N���X�̃C���X�^���X
	void Instances();

	void Walk(float elapsdTime);

	IBehaviorNode::State JumpAttack(float elapstTime);

	//�������U���@�r�w�C�r�A�c���[�ŌĂяo��
	IBehaviorNode::State BeamAttack(float elapsdTime);
	//�ߋ����U���@�r�w�C�r�A�c���[�ŌĂяo��
	IBehaviorNode::State CloseRangeAttack(float elapsdTime);

	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Enemy; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition()override { return m_position; }

	float GetHp() { return m_hp; }

	float GetMAXHp() { return m_maxHP; }

	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

	void Damage(const int  damage) override;


	//���݂̑傫���̎擾
	DirectX::SimpleMath::Vector3 GetScale() const override { return m_scale; }
	// ���݂̈ʒu���擾����
	//DirectX::SimpleMath::Vector3 GetPosition() const { return m_currentPosition; }
	// ���݂̈ʒu��ݒ肷��
	//void SetPosition(const DirectX::SimpleMath::Vector3& currretPosition) { m_currentPosition = currretPosition; }
	// ���݂̉�]�p���擾����
	DirectX::SimpleMath::Quaternion GetAngle() const override  { return m_rotate; }
	// ���݂̉�]�p��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) override { m_rotate = currentAngle; }
	// ���f�����擾����
	DirectX::Model* GetModel() override { return nullptr; }
	// ���[���h�s����擾����
	DirectX::SimpleMath::Matrix& GetWorldMatrix()  { return m_worldMatrix; }



	//�v���C���̂ق��Ɍ���  �r�w�C�r�A�c���[�ɂ�����Ȃ��̂����邩��ǂ��ɂ��������@�U���̗\�����쒆�ł��v���C���̕����������Ăق������炱���ɒǉ�����
	void  FacingThePlayer(float elapsdTime);

};