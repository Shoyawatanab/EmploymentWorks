/*
* �v���C���N���X�@
*/

#pragma once

#include "BaseEntity.h"

class CollisionManager;

namespace WataLib
{

	class Bounding;
}


class CollisionEntity : public BaseEntity
{
public:

	//�����蔻��̎��
	enum  class CollisionType
	{
		AABB = 1 << 0
		, OBB = 1 << 1
		, SPHERE = 1 << 2
	};

	//�����蔻��̃^�O
	enum class CollisionTag
	{
		NONE = 0
		, PLAYER = 1 << 0
		, PLAYERPARTS = 1 << 1
		, STAGE = 1 << 2
		, ENEMY = 1 << 3
		, ENEYPARTS = 1 << 4
		, BOOMERANG = 1 << 5
		, BEAM = 1 << 6
		, BARRIER = 1 << 7
	};

public:
	//�����蔻�肪�L�����ǂ���
	bool GetIsCollisionActive() { return m_isCollisionActive; }
	//�����蔻��̗L�����ǂ����̓o�^
	void SetIsCollisionActive(bool isActive) { m_isCollisionActive = isActive; }

public:

	//�R���X�g���N�^
	CollisionEntity(CommonResources* resources
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation) ;


	//������
	void Initialize() override;
	//�X�V����
	void  Update(const float& elapsedTime) override ;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override ;


	//�^�O�̎擾
	virtual CollisionTag GetCollisionTag() = 0;
	//�����������ɌĂяo�����
	virtual void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) { UNREFERENCED_PARAMETER(object); UNREFERENCED_PARAMETER(tag); };
	//�����葱���Ă���Ƃ��̌Ăяo�����
	virtual void OnCollisionStay(CollisionEntity* object, CollisionTag tag) { UNREFERENCED_PARAMETER(object); UNREFERENCED_PARAMETER(tag); };
	//�Փ˂��I�������Ƃ��ɌĂяo�����
	virtual void OnCollisionExit(CollisionEntity* object, CollisionTag tag) { UNREFERENCED_PARAMETER(object); UNREFERENCED_PARAMETER(tag); };
	//�����蔻��N���X�ɓo�^
	virtual void  AddCollision(CollisionManager* collsionManager);
	//�����蔻��̎擾
	WataLib::Bounding* GetBounding() { return m_bounding.get(); };
	//�����蔻��̎�ނ̎擾
	virtual const CollisionType GetCollisionType() = 0;
	//�����o�������邩�ǂ���
	virtual const bool GetIsExtrusion() = 0;
	//�����蔻����s��Ȃ��^�O
	virtual const std::vector<CollisionTag> GetNoHitDetectionTag() = 0;
	//���������I�u�W�F�N�g�̎擾
	const std::vector<CollisionEntity*> GetHitObject() { return m_hitObject; };
	//���������I�u�W�F�N�g�̓o�^
	void SetHitObject(CollisionEntity* object) { m_hitObject.push_back(object); };
	//���������I�u�W�F�N�g�̍폜
	void DleteHitObject(CollisionEntity* object, bool& isDelete) {
		size_t initialSize = m_hitObject.size();
		//�I�u�W�F�N�g������΍폜
		m_hitObject.erase(std::remove(m_hitObject.begin(), m_hitObject.end(), object), m_hitObject.end());
		//�폜�ł������ǂ���
		if (m_hitObject.size() < initialSize)
		{
			//�폜�ł�����
			isDelete = true;
		}
	};

	//�����o�����s��Ȃ��^�O
	virtual const std::vector<CollisionTag> GetNoExtrusionTag()  = 0;

private:
	//�����蔻��
	std::unique_ptr<WataLib::Bounding> m_bounding;
	//���������I�u�W�F�N�g�̊i�[�ϐ�
	std::vector<CollisionEntity*> m_hitObject;
	//�����蔻��̗L��
	bool m_isCollisionActive;

};


