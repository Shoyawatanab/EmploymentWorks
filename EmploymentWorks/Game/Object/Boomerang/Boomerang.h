#pragma once
/*
	@file	Boomerang.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Interface/IBoomerangState.h"
#include "Game/Object/Boomerang/State/BoomerangIdling.h"
#include "Game/Object/Boomerang/State/BoomerangThrow.h"
#include "Game/Object/Boomerang/State/BoomerangGetReady.h"
#include "Interface/ICollisionObject.h"
#include "Game/Object/Boomerang/State/BoomerangRepelled.h"
#include "Game/Object/Boomerang/State/BoomerangDrop.h"

// �O���錾
class CommonResources;
class Player;
class Bounding;
class BoomerangOrbit;
class PlayScene;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Boomerang : public ICollisionObject
{
public:

	//�g�p�����ǂ���
	enum class UseState
	{

		Stock,    //�X�g�b�N��ԁ@�@�@Update�E�`��Ȃ�
		Have,     //�����Ă�����   Update�Ȃ��E�`�悠��
		GetReady, // �\���Ă���@�@�@Update�E�`�悠��
		Throw     //�g�p��ԁ@�@�@�@�@Update�E�`�悠��

	};

public:
	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	void SetRotate(DirectX::SimpleMath::Quaternion Rotate) { m_rotate = Rotate; }

	float GetScale() { return m_scale; }

	Player* GetPlayer() { return m_player; }

	IBoomerangState* GetBoomerangState() { return m_currentState; }
	BoomerangIdling* GetBoomerangIdling() { return m_idling.get(); }
	BoomerangThrow* GetBoomerangThrow() { return m_throw.get(); }
	BoomerangGetReady* GetBoomerangGetReady() { return m_getReady.get(); }
	BoomerangRepelled* GetBoomerangRepelled() { return m_repelled.get(); }
	BoomerangDrop* GetBoomerangDrop() { return m_drop.get(); }


	BoomerangOrbit* GetOrbit() { return m_orbit.get(); }

	DirectX::SimpleMath::Vector3 GetPreviousFramePos() { return m_previousFramePos; }


	DirectX::SimpleMath::Vector3 GetBounceDirection() { return m_bounceDirection; }
	void SetBounceDirection(DirectX::SimpleMath::Vector3 direction) { m_bounceDirection = direction; }

	UseState GetUseState() { return m_useState; }
	void SetUseState(UseState State) { m_useState = State; }


private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	Player* m_player;

	std::unique_ptr<Bounding> m_bounding;

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	//�p�����[�^�[
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_rotate;
	float m_scale;


	std::unique_ptr<BoomerangOrbit> m_orbit;

	//���
	IBoomerangState* m_currentState;
	std::unique_ptr<BoomerangIdling> m_idling;
	std::unique_ptr<BoomerangThrow> m_throw;
	std::unique_ptr<BoomerangGetReady> m_getReady;
	std::unique_ptr<BoomerangRepelled> m_repelled;
	std::unique_ptr<BoomerangDrop> m_drop;


	Enemy* m_enemy;

	PlayScene* m_playScene;

	//�����������̑���̃^�O
	CollsionObjectTag m_onCollisionTag;

	//�P�t���[���O�̍��W�@�e����鏈���Ŏg�p

	DirectX::SimpleMath::Vector3 m_previousFramePos;

	//�u�[�������̒e��������
	DirectX::SimpleMath::Vector3 m_bounceDirection;

	//�X�g�b�N��Ԃ��g�p��Ԃ�
	UseState m_useState;



public:
	Boomerang();
	~Boomerang() ;

	void Initialize(CommonResources* resources) ;
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

	void ChangeState(IBoomerangState* nextState);

	void DemandBounceDirection(DirectX::SimpleMath::Vector3 pos, CollsionObjectTag& tag);


	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Boomerang; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition() override { return m_position; }

	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(Player* player, Enemy* enemy,PlayScene* playScene);

	//�N���X�̃C���X�^���X
	void Instances();

};
