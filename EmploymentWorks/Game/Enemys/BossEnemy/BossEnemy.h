/*
* �v���C���N���X�@
*/

#pragma once
#include "Game/Entities/EnemyEntity.h"
#include "Libraries/WataLib/Json.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Enemys/EnemyManager.h"
#include "Game/Enemys/BossEnemy/BehaviorTree/BehaviorTree.h"
#include "Game/Interface/IObserver.h"

#include "Game/Observer/Messenger.h"
#include "Libraries/WataLib/Shadow.h"
#include "Game/Enemys/EnemyManager.h"
#include"Game/Entities/ActionStateController.h"

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

class BossEnemy : public EnemyEntity  , public IObserver<GameMessageType> , public IObserver<EnemyMessageType>
{
public:

	static constexpr float PUNCHTIME{ 5.0f };


public:

	//�^�[�Q�b�g�̎擾
	BaseEntity* GetTarget() { return m_target; }
	//�^�[�Q�b�g�̓o�^
	void SetTarget(BaseEntity* target) { m_target = target; }
	//���n���Ă��邩�ǂ���
	bool GetIsGrounded() { return m_isGrounded; }
	//����g���Ă��邩�ǂ����̓o�^
	void SetIsGrounded(bool isGrounded) { m_isGrounded = isGrounded; }


public:
	//�R���X�g���N�^
	BossEnemy(CommonResources* resources,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//�f�X�g���N�^
	~BossEnemy() override;


	//������
	void Initialize() override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

	//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::ENEMY; };
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
			{CollisionTag::PLAYERPARTS}
			,{CollisionTag::ENEYPARTS}
			,{CollisionTag::BOOMERANG}
			,{CollisionTag::BEAM}
			,{CollisionTag::BARRIER}
		};
	}

	//�����o�����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};


	//�A�j���[�V�����̓o�^
	void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override;
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(std::string animationType) override;


//�ʒm���ɌĂ΂��֐�
	void Notify(const Telegram<GameMessageType>& telegram)  override;

	void Notify(const Telegram<EnemyMessageType>& telegram)  override;


	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(StageObjectManager* stageObjectManager);


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
			Messenger::GetInstance()->Notify(::GameMessageType::GAME_CLEAR, nullptr);
		}

	}

	//�r�w�C�r�A�c���[�Ŏg�p


	//�s���̕ύX
	void ChangeAction(const std::string actionName);
	

private:
	//�A�j���[�V�����f�[�^
	std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> m_animationDatas;
	//�r�w�C�r�A�c���[
	std::unique_ptr<BehaviorTree> m_behavior;
	//�v���C��
	Player* m_player;
	//�r�[��
	std::unique_ptr<Beam> m_beam;
	//�e
	std::unique_ptr<WataLib::Shadow> m_shadow;
	//�e����


	//�ۓ����I�����邩�ǂ���
	bool m_isAction;
	//�o���A
	std::unique_ptr<Barrier> m_barrier;

	//�^�[�Q�b�g
	BaseEntity* m_target;
	//�X�e�[�W�I�u�W�F�N�g�}�l�[�W���[
	StageObjectManager* m_stageObjectmanger;

	float m_gravity;
	//Hp
	int m_hp;

	//�p���`�U���̎���
	float m_punchTime;

	//���s�A�N�V����
	std::pair<std::string,ActionStateController*> m_action;
	//�A�N�V�����̕ۑ��ϐ�
	std::unordered_map<std::string, std::shared_ptr<ActionStateController>> m_actionList;

	//���n���Ă��邩�ǂ���
	bool m_isGrounded;

};


