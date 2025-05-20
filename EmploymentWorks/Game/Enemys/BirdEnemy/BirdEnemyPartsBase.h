#pragma once
#include "Game/Entities/CompositeEntity.h"

//�O���錾
class Player;


namespace WataLib
{
	class Animation;
}


class BirdEnemyPartsBase : public CompositeEntity
{

public:
	//���f���̎擾
	DirectX::Model* GetModel() { return m_model; }
	//���f���̓o�^
	void  SetModel(DirectX::Model* model) { m_model = model; }

public:
	//�R���X�g���N�^
	BirdEnemyPartsBase(CommonResources* resources,
		CharacterEntity* parent
		, std::string partsName,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//�f�X�g���N�^
	~BirdEnemyPartsBase()  override;

	//������
	void Initialize() override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::ENEYPARTS; };
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


	//�X�V����
	void  Update(const float& elapsedTime) override;

	//�A�j���[�V�����̓o�^
	void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override;
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(std::string animationType) override;

private:
	//���f��
	DirectX::Model* m_model;
	//�p�[�c��
	std::string m_partsName;
	//�������W
	DirectX::SimpleMath::Vector3 m_initialPosition;
	//�����X�P�[��
	DirectX::SimpleMath::Vector3 m_initialScale;
	//������]
	DirectX::SimpleMath::Quaternion m_initialRotation;





};
