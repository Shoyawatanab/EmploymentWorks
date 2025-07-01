#pragma once
#include "GameBase/Component.h"
#include "GameBase/Component/Transform/Transform.h"
#include "GameBase/Actor.h"

class CommonResources;

//���莞�̃^�C�v
enum class CollisionType
{

	FIXED     = 1 ,	   //�Œ�
	COLLISION = 2,	   //�ړ�
	TRIGGER   = 3      //���蔲��

};


class ColliderComponent : public Component
{
public:

	//�����蔻��̎��
	enum  class ColliderTag
	{
		AABB = 1 << 0
		, OBB = 1 << 1
		, SPHERE = 1 << 2
	};

public:	
	//�����蔻��̎�ނ̎擾
	const ColliderTag GetCollisionTag() { return m_collisionTag; }
	//���莞�̎�ނ̎擾
	CollisionType GetCollisionType() const { return m_collisionType; }

	//���������R���C�_�[�̎擾
	const std::vector<ColliderComponent*> GetHitObject() { return m_hitCollider; };
	//���������R���C�_�[�̓o�^
	void SetHitObject(ColliderComponent* ColliderComponent) { m_hitCollider.push_back(ColliderComponent); };
	//�����o��
	void SetPushBack(DirectX::SimpleMath::Vector3 puchBackVector);
	//�␳���W�̎擾
	const DirectX::SimpleMath::Vector3& OffsetPosition() { return m_offsetPosition; }
	//�␳���W�̃Z�b�g
	void SetOffsetPosition(DirectX::SimpleMath::Vector3 offset) {m_offsetPosition = offset; }
	//�����蔻����s��Ȃ��I�u�W�F�N�g�^�O�̃Z�b�g
	void SetNotHitObjectTag(std::vector<Actor::ObjectTag> tags) { m_notHitTag = tags; }
	//�����蔻����s��Ȃ��I�u�W�F�N�g�^�O�̎擾
	std::vector<Actor::ObjectTag> GetNotHitObjectTag() { return m_notHitTag; }

public:
	//�R���X�g���N�^
	ColliderComponent(Actor* owner,ColliderTag tag , CollisionType type);

	//�f�X�g���N�^
	virtual ~ColliderComponent() override;

	// �X�V����
	void Update(const float& deltaTime) override;
	//�h���p�̍X�V����
	virtual void UpdateCollider() {};
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
	, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch
	, DirectX::BasicEffect* effect
	, ID3D11InputLayout* inputlayout);
	//�h���p�̕`�揈��
	virtual void RenderCollider(const DirectX::SimpleMath::Matrix& view,const DirectX::SimpleMath::Matrix& projection
		, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch
		, DirectX::BasicEffect* effect
		, ID3D11InputLayout* inputlayout) {
		UNREFERENCED_PARAMETER(view);
		UNREFERENCED_PARAMETER(projection);
		UNREFERENCED_PARAMETER(batch);
		UNREFERENCED_PARAMETER(effect);
		UNREFERENCED_PARAMETER(inputlayout);
	};


	//���������R���C�_�[�̍폜
	bool DleteHitObject(ColliderComponent* object);

private:

	//�����蔻��̎��
	ColliderTag m_collisionTag;
	//���莞�̎��
	CollisionType m_collisionType;
	//���������I�u�W�F�N�g�̊i�[�ϐ�
	std::vector<ColliderComponent*> m_hitCollider;
	//�␳���W
	DirectX::SimpleMath::Vector3 m_offsetPosition;
	//�����蔻����s��Ȃ�Tag
	std::vector<Actor::ObjectTag> m_notHitTag;

};


class AABB : public ColliderComponent
{
public:
	//�o�E���f�B���O�{�b�N�X�̎擾
	DirectX::BoundingBox* GetBoundingBox();
	//�o�E���f�B���O�X�t�B�A�̎擾
	DirectX::BoundingSphere* GetBoundingSphere();

	//����Extents�̎擾
	DirectX::SimpleMath::Vector3 GetInitialExtents() { return m_initialExtents; }
	//�������a�̎擾
	float GetInitialRaduis() { return m_initialRadius; }

public:
	//�R���X�g���N�^
	AABB(Actor* owner, ColliderTag tag, CollisionType type
	,const DirectX::SimpleMath::Vector3& extents
	, const float& radius);
	//�f�X�g���N�^
	~AABB() override;

	//�h���p�̍X�V����
	void UpdateCollider() override ;
	//�h���p�̕`�揈��
	void RenderCollider(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
		, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch
		, DirectX::BasicEffect* effect
		, ID3D11InputLayout* inputlayout) override;

	//�{�b�N�X�̍X�V
	void BoxUpdate();
	//�X�t�B�A�̍X�V
	void SphereUpdate();

private:
	//�o�E���f�B���O�{�b�N�X
	std::unique_ptr<DirectX::BoundingBox> m_boundingBox;
	//�o�E���f�B���O�X�t�B�A
	std::unique_ptr<DirectX::BoundingSphere> m_boundingSphere;

	//����Extents
	DirectX::SimpleMath::Vector3 m_initialExtents;
	//�������a
	float m_initialRadius;

};


class OBB : public ColliderComponent
{
public:
	//�o�E���f�B���O�{�b�N�X�̎擾
	DirectX::BoundingOrientedBox* GetBoundingOrientedBox();
	//�o�E���f�B���O�X�t�B�A�̎擾
	DirectX::BoundingSphere* GetBoundingSphere();

	//����Extents�̎擾
	DirectX::SimpleMath::Vector3 GetInitialExtents() { return m_initialExtents; }
	//�������a�̎擾
	float GetInitialRaduis() { return m_initialRadius; }

public:
	//�R���X�g���N�^
	OBB(Actor* owner, ColliderTag tag, CollisionType type
		, const DirectX::SimpleMath::Vector3& extents
		,DirectX::SimpleMath::Quaternion rotation
		, const float& radius);
	//�f�X�g���N�^
	~OBB() override;

	//�h���p�̍X�V����
	void UpdateCollider() override;
	//�h���p�̕`�揈��
	void RenderCollider(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
		, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch
		, DirectX::BasicEffect* effect
		, ID3D11InputLayout* inputlayout) override;

	//�{�b�N�X�̍X�V
	void BoxUpdate();
	//�X�t�B�A�̍X�V
	void SphereUpdate();


private:
	//�o�E���f�B���O�{�b�N�X
	std::unique_ptr<DirectX::BoundingOrientedBox> m_boundingOrientedBox;
	//�o�E���f�B���O�X�t�B�A
	std::unique_ptr<DirectX::BoundingSphere> m_boundingSphere;

	//����Extents
	DirectX::SimpleMath::Vector3 m_initialExtents;
	//�������a
	float m_initialRadius;

};
