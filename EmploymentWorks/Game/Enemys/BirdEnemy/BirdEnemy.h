/*
* �v���C���N���X�@
*/

#pragma once
#include "Game/Entities/EnemyEntity.h"
#include "Libraries/WataLib/Json.h"
#include "Game/Enemys/EnemyManager.h"
#include "Game/Interface/IObserver.h"

#include "Game/Observer/Messenger.h"
#include "Game/Enemys/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Libraries/WataLib/Shadow.h"

// �O���錾
class CommonResources;
class EnemyManager;
class Player;
class BirdEnemyBeam;



namespace WataLib
{
	class Bounding;
}

class BirdEnemy : public EnemyEntity
{

public:

	BirdEnemyStateMachine* GetPlayerStateMachine() { return m_stateMachine.get(); };

	DirectX::SimpleMath::Vector3 GetBeamPosition() { return m_beamPosition; };

	std::vector<std::unique_ptr<BirdEnemyBeam>>& GetBeams() { return m_beam; }


public:

	//�R���X�g���N�^
	BirdEnemy(CommonResources* resources
		, DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//�f�X�g���N�^
	~BirdEnemy() override;

	//IObject
		//������
	void Initialize() override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;


	//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::ENEYPARTS; };
	//�����蔻��N���X�ɓo�^
	void  AddCollision(CollisionManager* collsionManager) override;

	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//�����蔻��̎�ނ̎擾
	const CollisionType GetCollisionType() override { return CollisionType::AABB; }
	//�����o�������邩�ǂ���
	const bool GetIsExtrusion() override { return true; };
	//�����蔻����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::PLAYERPARTS}
			,{CollisionTag::ENEYPARTS}
			,{CollisionTag::BEAM}
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

	void Rotate(float elapsedTime);

private:
	//�錾
	//�G�}�l�[�W���[
	EnemyManager* m_enemyManager;
	//�v���C��
	Player* m_player;
	//�e
	std::unique_ptr<WataLib::Shadow> m_shadow;
	//Hp
	int m_hp;

	//�p���`�U���̎���
	float m_punchTime;


	//�X�e�[�g�}�V��
	std::unique_ptr<BirdEnemyStateMachine>  m_stateMachine;
	//�r�[���̐������W
	DirectX::SimpleMath::Vector3 m_beamPosition;
	//�r�[��
	std::vector<std::unique_ptr<BirdEnemyBeam>> m_beam;



};


