#pragma once
/*
	@file	Wall.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Entities/INotMoveEntity.h"

namespace WataLib
{
	class Bounding;
}


class Wall : public INotMoveEntity

{
public:
	//�R���X�g���N�^
	Wall(CommonResources* resources
		,DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);

	//�f�X�g���N�^
	~Wall() override;

	//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

	//ICollisionObject
	//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::STAGE; };
	//�����蔻��̎�ނ̎擾
	const CollisionType GetCollisionType() override { return CollisionType::AABB; };
	//�����o�������邩�ǂ���
	const bool GetIsExtrusion() override { return false; };
	//�����蔻����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::STAGE }
		};
	};

	//�����o�����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};



private:
	// ���f��
	DirectX::Model* m_model;




};
