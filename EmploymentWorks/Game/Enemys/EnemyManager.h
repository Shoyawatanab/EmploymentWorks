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


	void CreateEnemy();

	void AddEnemyData(WataLib::Json::StageData enemyData);


	//�����蔻��N���X�ɓo�^
	void  AddCollision(CollisionManager* collsionManager);

	std::vector<std::unique_ptr<EnemyEntity>>& GetEnemys() { return m_enemys; }

	//�Ō�̓G�̎擾
	EnemyEntity* GetLastEnemy() { return m_remainingEnemys[0]; }

	//�c���Ă���G�̍폜
	void DeleteRemainingEnemy(EnemyEntity* character) 
	{

		if (m_remainingEnemys.size() <= 1) {
			Messenger::Notify(EventParams::EventType::GameClear, nullptr);
			Messenger::Notify(EventParams::EventType::DefeatedAllEnemies, nullptr);
			return;
		}

		// �w�肳�ꂽ�L�����N�^�[��T���č폜
		auto it = std::find(m_remainingEnemys.begin(), m_remainingEnemys.end(), character);
		if (it != m_remainingEnemys.end()) {
			m_remainingEnemys.erase(it); // ���������ꍇ�͍폜
		}
	}


	//�{�X��HP�����̎擾
	float GetBossHPRation();

	BossEnemy* GetBossEnemy() { return m_bossEnemy; }

	std::vector<WataLib::Json::StageData> m_enemyDatas;

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�G�z��
	std::vector<std::unique_ptr<EnemyEntity>> m_enemys;

	std::vector<EnemyEntity*> m_remainingEnemys;

	Player* m_player;
	StageObjectManager* m_stageObjectmanger;

	BossEnemy* m_bossEnemy;

};
