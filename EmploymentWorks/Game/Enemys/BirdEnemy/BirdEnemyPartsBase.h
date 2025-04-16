#pragma once
#include "Game/Entities/CompositeEntity.h"

class Player;


namespace WataLib
{
	class Animation;
}


class BirdEnemyPartsBase : public CompositeEntity
{

public:

	DirectX::Model* GetModel() { return m_model; }
	void  SetModel(DirectX::Model* model) { m_model = model; }

public:
	BirdEnemyPartsBase(CommonResources* resources,
		CharacterEntity* parent
		, std::string partsName,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);


	~BirdEnemyPartsBase()  override;


	//IObject
	//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//ICollisionObject
	//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::EnemyParts; };
	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//�����蔻��̎�ނ̎擾
	const CollisionType GetCollisionType() override { return CollisionType::OBB; };
	//�����o�������邩�ǂ���
	const bool GetIsExtrusion() override { return true; };
	//�����蔻����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
		};
	};
	//�����o�����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};


	//IMoveObject
	//�X�V����
	void  Update(const float& elapsedTime) override;

	//ICharacter
	//�A�j���[�V�����̓o�^
	void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override;
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(std::string animationType) override;

private:
	//
	DirectX::Model* m_model;
	//�p�[�c��
	std::string m_partsName;

	DirectX::SimpleMath::Vector3 m_initialPosition;

	DirectX::SimpleMath::Vector3 m_initialScale;

	DirectX::SimpleMath::Quaternion m_initialRotation;





};
