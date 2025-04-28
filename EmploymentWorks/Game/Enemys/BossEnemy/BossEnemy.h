/*
* �v���C���N���X�@
*/

#pragma once
#include "Game/Entities/EnemyEntity.h"
#include "Libraries/WataLib/Json.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Interface/IWeapon.h"
#include "Game/Enemys/EnemyManager.h"
#include "Game/Enemys/BossEnemy/BehaviorTree/BehaviorTree.h"
#include "Game/Interface/IObserver.h"

#include "Game/Observer/Messenger.h"
#include "Libraries/WataLib/Shadow.h"
#include "Game/Enemys/EnemyManager.h"
#include "Game/Interface/IActione.h"

// �O���錾
class CommonResources;
class Boomerang;
class EnemyManager;
class BehaviorTree;
class Player;
class Beam;
class StageObjectManager;
class Barrier;


namespace WataLib
{
	class Bounding;
}

class BossEnemy : public EnemyEntity  , public IObserver
{
public:

	static constexpr float PUNCHTIME{ 5.0f };

	enum class AttackState
	{
		None
		,End
		,Beam
	};

public:

	BaseEntity* GetTarget() { return m_target; }

	void SetTarget(BaseEntity* target) { m_target = target; }

	DirectX::SimpleMath::Vector3 GetVelocity() { return m_velocity; }

	void SetVelocity(DirectX::SimpleMath::Vector3  velocity) { m_velocity = velocity; }

	bool GetIsGrounded() { return m_isGrounded; }

	void SetIsGrounded(bool isGrounded) { m_isGrounded = isGrounded; }

public:
	//�R���X�g���N�^
	BossEnemy(CommonResources* resources,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//�f�X�g���N�^
	~BossEnemy() override;

	//IObject
	//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

	//ICollisionObject
		//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Enemy; };
	//�����蔻��N���X�ɓo�^
	void  AddCollision(CollisionManager* collsionManager) override;

	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//�����葱���Ă���Ƃ��̌Ăяo�����
	void OnCollisionStay(CollisionEntity* object, CollisionTag tag) override;

	void OnCollisionExit(CollisionEntity* object, CollisionTag tag) override;

	//�����蔻��̎�ނ̎擾
	const CollisionType GetCollisionType() override { return CollisionType::AABB; }
	//�����o�������邩�ǂ���
	const bool GetIsExtrusion() override { return true; };
	//�����蔻����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::PlayerParts}
			,{CollisionTag::EnemyParts}
			,{CollisionTag::Boomerang}
			,{CollisionTag::Beam}
			,{CollisionTag::Barrier}
		};
	}

	//�����o�����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};


	//ICharacter
		//�A�j���[�V�����̓o�^
	void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override;
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(std::string animationType) override;


//�ʒm���ɌĂ΂��֐�
	void Notify(const Telegram& telegram)  override;


	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(Player* player, StageObjectManager* stageObjectManager);


	//HP�̎擾
	int& GetHP() { return m_hp; }

	//�_���[�W
	void Damage(int damage) {
		m_hp -= damage;

		if (m_hp <= 0 && m_hp + damage > 0)
		{
			//�|���A�j���[�V�����ɐ؂�ւ���
			ChangeAnimation("FallDown");
			EnemyEntity::GetEnemyManager()->DeleteRemainingEnemy(this);
			Messenger::GetInstance()->Notify(::MessageType::GameClear, nullptr);
		}

	}

	//�r�w�C�r�A�c���[�Ŏg�p


	//�s���̕ύX
	void ChangeAction(std::string actionName);
	

private:
	//�A�j���[�V�����f�[�^
	std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> m_animationDatas;
	//�r�w�C�r�A�c���[
	std::unique_ptr<BehaviorTree> m_behavior;
	//�v���C��
	Player* m_player;
	//�r�[��
	std::unique_ptr<Beam> m_beam;
	//�U�����
	AttackState m_attackState;
	//�e
	std::unique_ptr<WataLib::Shadow> m_shadow;
	//�e����


	//�ۓ����I�����邩�ǂ���
	bool m_isAction;

	std::unique_ptr<Barrier> m_barrier;

	//�^�[�Q�b�g
	BaseEntity* m_target;

	StageObjectManager* m_stageObjectmanger;

	float m_gravity;
	//Hp
	int m_hp;

	//�p���`�U���̎���
	float m_punchTime;

	bool m_isActives;

	DirectX::SimpleMath::Vector3 m_velocity;



	std::pair<std::string,IAction*> m_action;

	std::unordered_map<std::string, std::unique_ptr<IAction>> m_actionList;

	//���n���Ă��邩�ǂ���
	bool m_isGrounded;

};


