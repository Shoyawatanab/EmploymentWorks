#pragma once
#include "Game/Entities/CompositeEntity.h"
#include "Game/Observer/EventParams.h"

class CommonResources;
class BossEnemy;

namespace WataLib
{
	class Animation;
}



class BossEnemyPartsBase : public CompositeEntity
{

public:
	//���f���̎擾
	DirectX::Model* GetModel() { return m_model; }
	//���f���̓o�^
	void  SetModel(DirectX::Model* model) { m_model = model; }
	//���[�g�̎����
	BossEnemy* GetRoot() { return m_root; }
	//�p�[�cHP�̎擾
	const int& GetPartsHP() { return m_partsHP; }

	/// <summary>
	/// �p�[�c�j�󂳂�Ă��邩�ǂ����̎擾
	/// </summary>
	/// <returns>ture:�j�󂳂�Ă��� false:�j�󂳂�Ă��Ȃ�</returns>
	const bool& GetIsPartDestruction() { return m_isPartDestruction; }
	//�p�[�c�j�󂳂�Ă��邩�ǂ����̓o�^
	void SetIsPartDestruction(bool isPartDestruction) { m_isPartDestruction = isPartDestruction;; }

public:
	// �R���X�g���N�^
	BossEnemyPartsBase(CommonResources* resources
		, BossEnemy* root,
		CharacterEntity* parent,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		std::string partsName,
		int partsHP
		, DirectX::SimpleMath::Vector3 boxColliderSize,
		float SphereColliderSize);
	//�f�X�g���N�^
	~BossEnemyPartsBase()  override;


	
	//������
	void Initialize() override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::ENEYPARTS; };
	//�����蔻��N���X�ɓo�^
	void  AddCollision(CollisionManager* collsionManager) override;
	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//�����蔻��̎�ނ̎擾
	const CollisionType GetCollisionType() override { return CollisionType::OBB; };
	//�����o�������邩�ǂ���
	const bool GetIsExtrusion() override { return true; };
	//�����蔻����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::PLAYERPARTS}
			,{CollisionTag::ENEMY}
			,{CollisionTag::ENEYPARTS}

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



	//�p�[�c�ɑ΂��ă��b�Z�[�W�𑗂�
	void NotifyParts(PartMessageType type);

private:
	//���f��
	DirectX::Model* m_model;
	//�p�[�c��
	std::string m_partsName;
	//�������W
	DirectX::SimpleMath::Vector3 m_initialPosition;
	//�����̑傫��
	DirectX::SimpleMath::Vector3 m_initialScale;
	//������]
	DirectX::SimpleMath::Quaternion m_initialRotation;
	//�p�[�cHP
	int m_partsHP;
	//�l�p�̓����蔻��̑傫��
	DirectX::SimpleMath::Vector3 m_boxColliderSize;
	//�~�̓����蔻��̑傫��
	float m_sphereColliderSize;
	//���{�̃N���X
	BossEnemy* m_root;
	//�p�[�c�j�󂳂�Ă��邩
	bool m_isPartDestruction;


};
