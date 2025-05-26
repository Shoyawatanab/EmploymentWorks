#pragma once
/*
	@file	EnemyManager.h.h
	@brief	�G�̊Ǘ��N���X
*/
#pragma once
#include "pch.h"
#include "Game/Entities/EnemyEntity.h"
#include "Libraries/WataLib/Json.h"
#include "Game/Observer/Messenger.h"

// �O���錾
class CommonResources;
class Player;
class BossEnemy;
class StageObjectManager;

class EnemyManager 
{
public:
	//�{�X�e�L�̎擾
	BossEnemy* GetBossEnemy() { return m_bossEnemy; }

	//�{�X��HP�����̎擾
	float GetBossHPRation();
	//���ׂĂ̓G���̎擾
	std::vector<std::unique_ptr<EnemyEntity>>& GetEnemys() { return m_enemys; }


public:
	//�R���X�g���N�^
	EnemyManager(Player* player, StageObjectManager* stageObjectmanger);
	//�f�X�g���N�^
	~EnemyManager() ;
	//������
	void Initialize(CommonResources* resources);
	//�X�V����
	void Update(const float& elapsedTime);
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	//
	void Finalize() ;
	//�G���̒ǉ�
	void AddEnemyData(WataLib::Json::ObjectData enemyData);

	//�����蔻��N���X�ɓo�^
	void  AddCollision(CollisionManager* collsionManager);


	//�Ō�̓G�̎擾
	EnemyEntity* GetLastEnemy() { return m_remainingEnemys[0]; }

	//�c���Ă���G�̍폜
	void DeleteRemainingEnemy(EnemyEntity* character) 
	{

		if (m_remainingEnemys.size() <= 1) {
			Messenger::GetInstance()->Notify(GameMessageType::GAME_CLEAR, nullptr);
			Messenger::GetInstance()->Notify(GameMessageType::DEFEATED_All_ENEMIES, nullptr);
			return;
		}

		// �w�肳�ꂽ�L�����N�^�[��T���č폜
		auto it = std::find(m_remainingEnemys.begin(), m_remainingEnemys.end(), character);
		if (it != m_remainingEnemys.end()) {
			m_remainingEnemys.erase(it); // ���������ꍇ�͍폜
		}
	}






private:

	void CreateEnemy();

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�G�z��
	std::vector<std::unique_ptr<EnemyEntity>> m_enemys;
	//�c��̓G
	std::vector<EnemyEntity*> m_remainingEnemys;
	//�v���C��
	Player* m_player;
	//�X�e�[�W�I�u�W�F�N�g�}�l�[�W���[
	StageObjectManager* m_stageObjectmanger;
	//�{�X�G
	BossEnemy* m_bossEnemy;
	//�G���
	std::vector<WataLib::Json::ObjectData> m_enemyDatas;


};
