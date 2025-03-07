/*
* �v���C���N���X�@
*/

#pragma once

#include "MoveEntity.h"
#include <unordered_map>
#include "Libraries/WataLib/Json.h"

namespace WataLib
{
	class Animation;
}

class ItemEntity : public MoveEntity
{
public:


	ItemEntity(CommonResources* resources
		,const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);

	~ItemEntity() override;

//BaseEntity
	//������
	void Initialize();
	//�X�V����
	void  Update(const float& elapsedTime)  override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
//CollisionEntity
	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;

	//�����
	virtual void OnAcquired() {}

private:



};


