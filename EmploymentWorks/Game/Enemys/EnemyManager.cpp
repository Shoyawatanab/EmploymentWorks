/*
	@file	EnemyManager.cpp
	@brief	
*/
#include "pch.h"
#include "EnemyManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include <cassert>
#include "Game/CollisiionManager.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/Params.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="stageObjectmanger">�X�e�[�W�I�u�W�F�N�g�}�l�[�W���[</param>
EnemyManager::EnemyManager(Player* player, StageObjectManager* stageObjectmanger)
	:
	m_commonResources{}
	,m_enemys{}
	,m_remainingEnemys{}
	,m_player{player}
	,m_bossEnemy{}
	,m_enemyDatas{}
	,m_stageObjectmanger{stageObjectmanger}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyManager::~EnemyManager()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void EnemyManager::Initialize(CommonResources* resources)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;

	//�G�̐���
	CreateEnemy();

	//�c��̓G�̕ϐ��ɑ��
	for (auto& enemy : m_enemys)
	{
		m_remainingEnemys.push_back(enemy.get());
	}
	
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void EnemyManager::Update(const float& elapsedTime)
{
	//�G�̍X�V
	for (auto& enemy : m_enemys)
	{
		enemy->Update(elapsedTime);
	}

}


/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void EnemyManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX::SimpleMath;

	//�G�̕`��
	for (auto& enemy : m_enemys)
	{
		enemy->Render(view, projection);
	}

}

void EnemyManager::Finalize()
{
	// do nothing.
}



/// <summary>
/// �G�̐���
/// </summary>
void EnemyManager::CreateEnemy()
{
	for (auto& enemyData : m_enemyDatas)
	{
		//�G�̎��
		std::string kind = enemyData.ModelName;


		if (kind == "BossEnemy")
		{
			auto enemy = std::make_unique<BossEnemy>(m_commonResources
				, enemyData.Scale, enemyData.Position,
				DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
					DirectX::XMConvertToRadians(enemyData.Rotation.y),
					DirectX::XMConvertToRadians(enemyData.Rotation.x),
					DirectX::XMConvertToRadians(enemyData.Rotation.z))
			);
			enemy->SetManager(this);
			enemy->AddPointer(m_player,m_stageObjectmanger);
			enemy->Initialize();

			m_bossEnemy = enemy.get();

			m_enemys.push_back(std::move(enemy));

		}
		else if (kind == "BirdEnemy")
		{
			auto enemy = std::make_unique<BirdEnemy>(m_commonResources
			, enemyData.Scale, enemyData.Position, 
				DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
					DirectX::XMConvertToRadians(enemyData.Rotation.y),
					DirectX::XMConvertToRadians(enemyData.Rotation.x),
					DirectX::XMConvertToRadians(enemyData.Rotation.z))
			);
			enemy->SetManager(this);
			enemy->AddPointer(m_player);
			enemy->Initialize();


			m_enemys.push_back(std::move(enemy));
		}

	}


}

/// <summary>
/// �G�f�[�^�̒ǉ�
/// </summary>
/// <param name="enemyData">�f�[�^</param>
void EnemyManager::AddEnemyData(WataLib::Json::StageData enemyData)
{

	m_enemyDatas.push_back(enemyData);

}

/// <summary>
/// �����蔻��N���X�ɒǉ�
/// </summary>
/// <param name="collsionManager">�����蔻��N���X</param>
void EnemyManager::AddCollision(CollisionManager* collsionManager)
{
	for (auto& enemy : m_enemys)
	{
		enemy->AddCollision(collsionManager);
	}
}


/// <summary>
/// �{�X��HP�����̎擾
/// </summary>
/// <returns>����</returns>
float EnemyManager::GetBossHPRation()
{
	//���������߂�
	float ration = m_bossEnemy->GetHP() / static_cast<float>(Params::BOSSENEMY_MAX_HP);
	return ration;
}


