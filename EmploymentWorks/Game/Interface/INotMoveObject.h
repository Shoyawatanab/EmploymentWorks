/*
* �����Ȃ��I�u�W�F�N�g�̃C���^�[�t�F�[�X
*/
#pragma once
#include "Game/Interface/ICollisionObject.h"


class INotMoveObject : public ICollisionObject
{
public:
	//�f�X�g���N�^
	virtual ~INotMoveObject() = default;

	//��{���̐ݒ�
	virtual void SetDatas(DirectX::SimpleMath::Vector3 scale, 
		DirectX::SimpleMath::Vector3 position, 
		DirectX::SimpleMath::Quaternion rotation) = 0;

};
