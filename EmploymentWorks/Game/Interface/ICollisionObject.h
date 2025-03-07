/*
* �����蔻��̃C���^�[�t�F�[�X
*/
#pragma once
#include "Game/Interface/IObject.h"

class CollisionManager;

namespace WataLib
{

	class Bounding;
}


class ICollisionObject : public IObject
{
public:
	enum  class CollisionType
	{
		AABB = 1 << 0
		,OBB = 1 << 1
		,SPHERE = 1 << 2
	};

	enum class CollisionTag
	{
		None = 0
		, Player = 1 << 0
		, PlayerParts  = 1 << 1
		,Stage  = 1 <<2
		,Enemy = 1 << 3
		,EnemyParts = 1 << 4
		,Boomerang = 1 << 5
		,Beam = 1 << 6
	};


public:
	//�f�X�g���N�^
	virtual ~ICollisionObject() = default;
	//�^�O�̎擾
	virtual CollisionTag GetCollisionTag() = 0;
	//�����������ɌĂяo�����
	virtual void OnCollisionEnter(ICollisionObject* object, CollisionTag tag) = 0;
	//�����蔻��N���X�ɓo�^
	virtual void  AddCollision(CollisionManager* collsionManager) = 0;
	//�����蔻��̎擾
	virtual WataLib::Bounding* GetBounding() = 0;
	//�����蔻��̎�ނ̎擾
	virtual const CollisionType GetCollisionType() = 0;
	//�����o�������邩�ǂ���
	virtual const bool GetIsExtrusion() = 0;
	//�����蔻����s��Ȃ��^�O
	virtual const std::vector<CollisionTag> GetNoHitDetectionTag() = 0;
	//���������I�u�W�F�N�g�̎擾
	virtual const std::vector<ICollisionObject*> GetHitObject() = 0;
	//���������I�u�W�F�N�g�̓o�^
	virtual void SetHitObject(ICollisionObject* object) = 0;
	//���������I�u�W�F�N�g�̍폜
	virtual void DleteHitObject(ICollisionObject* object,bool& isDelete) = 0;
};
