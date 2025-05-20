/*
* �v���C���N���X�@
*/

#pragma once

#include "CollisionEntity.h"


class INotMoveEntity : public CollisionEntity
{
public:
	//�R���X�g���N
	INotMoveEntity(CommonResources* resources
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//�f�X�g���N�^
	~INotMoveEntity() override;

	//������
	void Initialize() override;
	//�X�V����
	void  Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;


};


