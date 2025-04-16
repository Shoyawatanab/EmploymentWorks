#pragma once
#include "Game/Entities/ItemEntity.h"
#include "Game/Weapon/Boomerang/State/BoomerangIdle.h"
#include "Libraries/WataLib/Shadow.h"

using namespace DirectX::SimpleMath;

// �O���錾
class CommonResources;
class BoomerangStateMachine;
class Player;
class TargetMarker;

namespace WataLib
{
	class Bounding;
	class TPS_Camera;
}



class Boomerang : public ItemEntity
{
public:

	BoomerangStateMachine* GetBoomerangStatemachine() { return m_stateMachine.get(); }

	std::vector<DirectX::SimpleMath::Vector3>& GetThrowBasePosition() { return m_throwbasePosition; }

	const Vector3& GetPrevPosition() { return m_prevPosition; }

public:
	//�R���X�g���N�^
	Boomerang(CommonResources* resources
		, BaseEntity* parent
		, DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//�f�X�g���N�^
	~Boomerang() override;

	//IObject
		//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

	//ICollisionObject
	//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Boomerang; };
	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//�Փ˂��I�������Ƃ��ɌĂяo�����
	void OnCollisionExit(CollisionEntity* object, CollisionTag tag);

	//�����蔻��̎�ނ̎擾
	const CollisionType GetCollisionType() override { return CollisionType::AABB; };
	//�����o�������邩�ǂ���
	const bool GetIsExtrusion() override { return false; };
	//�����蔻����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoHitDetectionTag() override {
		return  {
			//{CollisionTag::Player},
			{CollisionTag::PlayerParts}
			,{CollisionTag::Boomerang}
			,{CollisionTag::Enemy}

		};
	};

	//�����o�����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};


	void OnAcquired() override ;


	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(Player* player, TargetMarker* targetMarker, WataLib::TPS_Camera* tpsCamera);

private:
	//�e
	BaseEntity* m_parent;
	//���f��
	DirectX::Model* m_model;

	//�X�e�[�g�}�V��
	std::unique_ptr<BoomerangStateMachine> m_stateMachine;

	//�������W
	DirectX::SimpleMath::Vector3 m_initialPosition;
	//
	DirectX::SimpleMath::Vector3 m_initialScale;

	DirectX::SimpleMath::Quaternion m_initialRotation;
	//������O���̊���W
	std::vector<DirectX::SimpleMath::Vector3> m_throwbasePosition;


	std::unique_ptr<WataLib::Shadow> m_shadow;
	//1�t���O�̍��W
	DirectX::SimpleMath::Vector3 m_prevPosition;

	bool m_isCatch;

};