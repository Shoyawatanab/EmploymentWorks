#pragma once
/*
	@file	Floor.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Entities/INotMoveEntity.h"

namespace WataLib
{
	class Bounding;
}

class Floor : public INotMoveEntity
{
private:

	static constexpr DirectX::SimpleMath::Vector3 BOX_COLLIDER_SIZE {0.35, 0.1, 0.35};

	static constexpr float SPHERE_COLLIDER_SIZE{ 60.0 };

public:
	//�R���X�g���N�^
	Floor(CommonResources* resources
		,DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);


	//�f�X�g���N�^
	~Floor() override;

	//IObject
		//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

	//ICollisionObject
	//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Stage; };
	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//�����蔻��̎�ނ̎擾
	const CollisionType GetCollisionType() override { return CollisionType::AABB; };
	//�����o�������邩�ǂ���
	const bool GetIsExtrusion() override { return false; };
	//�����蔻����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::Stage }
		};
	};

	//�����o�����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};


	//��{���̐ݒ�
	void SetDatas(DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);

private:
	// ���f��
	std::unique_ptr<DirectX::Model> m_model;




};
