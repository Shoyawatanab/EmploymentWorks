/*
* �v���C���N���X�@
*/

#pragma once
#include "Game/Entities/CompositeEntity.h"
#include "Libraries/WataLib/Json.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/Interface/IWeapon.h"
#include "Game/TargetMarker.h"
#include "Libraries/WataLib/Shadow.h"

// �O���錾
class CommonResources;
class PlayerUsually;
class PlayerStateMachine;
class Boomerang;


namespace WataLib
{
	class TPS_Camera;
	class Bounding;
}

class Player : public CompositeEntity 
{
private:


public:

	PlayerStateMachine* GetPlayerStateMachine() { return m_stateMachine.get(); };

	std::vector<std::unique_ptr<Boomerang>>* GetBoomerangs() { return &m_boomerangs; }

	/// <summary>
	/// �u�[�������̎擾�iState���Y������N���X�Ɠ����N���X���j
	/// </summary>
	/// <typeparam name="T">State�N���X</typeparam>
	/// <returns>�Y������N���X�i�z��̏��߂̕����璲�ׂ�j</returns>
	template<typename T>
	Boomerang* GetBoomerang()
	{
		auto it = std::find_if(m_boomerangs.begin(), m_boomerangs.end(),
			[](const std::unique_ptr<Boomerang>& boomerang) {
				return typeid(*boomerang->GetBoomerangStatemachine()->GetCurrentState()) == typeid(T);
			});

		// ������Ȃ��ꍇ�� nullptr ��Ԃ�
		return (it != m_boomerangs.end()) ? it->get() : nullptr;
	};


public:
	//�R���X�g���N�^
	Player(CommonResources* resources);

	//�f�X�g���N�^
	~Player() override;

//IObject
	//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;


//ICollisionObject
	//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Player; };
	//�����蔻��N���X�ɓo�^
	void  AddCollision(CollisionManager* collsionManager) override ;

	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//�����葱���Ă���Ƃ��̌Ăяo�����
	void OnCollisionStay(CollisionEntity* object, CollisionTag tag) override;

	//�����蔻��̎�ނ̎擾
	const CollisionType GetCollisionType() override { return CollisionType::AABB; }
	//�����o�������邩�ǂ���
	const bool GetIsExtrusion() override { return true; };
	//�����蔻����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::PlayerParts}
			//,{CollisionTag::Boomerang}
		};
	}

	//�����o�����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
			{CollisionTag::Boomerang}
		};
	};


//ICharacter
	//�A�j���[�V�����̓o�^
	void SetAnimationData(std::string animationType
		,std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override;
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(std::string animationType) override;

	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(WataLib::TPS_Camera* tpsCamera, TargetMarker* targetMarker);

private:
	//�錾

	//����
	std::unique_ptr<PlayerUsually> m_usually;
	//�A�j���[�V�����f�[�^
	std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> m_animationDatas;
	//�X�e�[�g�}�V��
	std::unique_ptr<PlayerStateMachine>  m_stateMachine;

	//�u�[������
	std::vector<std::unique_ptr<Boomerang>> m_boomerangs;
	//�g�p���̃u�[������
	Boomerang* m_currentBoomerang;
	//
	TargetMarker* m_targetMarker;
	//HP
	int m_hp;
	// �e�I�u�W�F�N�g
	std::unique_ptr<WataLib::Shadow> m_shadow;

};


