#pragma once
#ifndef IMoveCollisionObject_DEFINED
#define IMoveCollisionObject_DEFINED
#include "Interface/ICollisionObject.h"



// ICollisionObject�C���^�t�F�[�X���`����(GOF State�p�^�[��)
class IMoveCollisionObject : public ICollisionObject
{
public:

	virtual void SetPos(DirectX::SimpleMath::Vector3& Pos) = 0;

};

#endif		// ICollisionObject_DEFINED
