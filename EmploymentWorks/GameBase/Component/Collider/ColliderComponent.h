#pragma once
#include "GameBase/Component.h"
#include "GameBase/Component/Transform/Transform.h"

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

	//���W�̍X�V
	virtual void PositionUpdate() = 0;

private:

	//�����蔻��̎��
	ColliderTag m_collisionTag;
	//���莞�̎��
	CollisionType m_collisionType;
	//���������I�u�W�F�N�g�̊i�[�ϐ�
	std::vector<ColliderComponent*> m_hitCollider;


};


class AABB : public ColliderComponent
{
public:
	//�o�E���f�B���O�{�b�N�X�̎擾
	DirectX::BoundingBox* GetBoundingBox();
	//�o�E���f�B���O�X�t�B�A�̎擾
	DirectX::BoundingSphere* GetBoundingSphere();
	//DirectX::BoundingOrientedBox* GetOrientedBox() { return m_orientexBox.get(); }

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

	//���W�̍X�V
	void PositionUpdate() override;


private:
	//�o�E���f�B���O�{�b�N�X
	std::unique_ptr<DirectX::BoundingBox> m_boundingBox;
	//�o�E���f�B���O�X�t�B�A
	std::unique_ptr<DirectX::BoundingSphere> m_boundingSphere;


};