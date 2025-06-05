#include "pch.h"
#include "BossEnemyHP.h"
#include "Libraries/WataLib/UserInterface.h"
#include "Game/Observer/Messenger.h"

/// <summary>
/// 
/// </summary>
BossEnemyHP::BossEnemyHP(CommonResources* resources)
	:
	UIBaseEntity(resources)
	,m_enemyHPBase{}
{
}

/// <summary>
/// 
/// </summary>
BossEnemyHP::~BossEnemyHP()
{
}

void BossEnemyHP::Initialize()
{

	//���N���X�̏�����
	UIBaseEntity::Initialize();


	m_enemyHPBase = std::make_unique<UserInterface>();
	m_enemyHPBase->Create(UIBaseEntity::GetCommonResources()
		, "BossHPBase"
		, ENEMY_HP_BASE_POSITION
		, ENEMY_HP_BASE_SCALE
	);


	
	m_enemyHP = std::make_unique<UserInterface>();
	m_enemyHP->Create(UIBaseEntity::GetCommonResources()
		, "EnemyHP"
		, ENEMY_HP_POSITION
		, ENEMY_HP_SCALE
	);


	m_enemyName = std::make_unique<UserInterface>();
	m_enemyName->Create(UIBaseEntity::GetCommonResources()
		, "EnemyName"
		, ENEMY_NAME_POSITION
		, ENEMY_NAME_SCALE
	);


	Messenger::GetInstance()->Rigister(GamePlayMessageType::BOSS_DAMAGE, this);

}

void BossEnemyHP::Update(const float& elapsedTime)
{
	//�I�u�W�F�N�g��������Update�������Ȃ�
	if (!UIBaseEntity::GetIsEntityActive() || !UIBaseEntity::GetIsUpdateActive())
	{
		return;
	}

	//���N���X�̍X�V����
	UIBaseEntity::Update(elapsedTime);




}

void BossEnemyHP::Render()
{

	//�I�u�W�F�N�g��������Update�������Ȃ�
	if (!UIBaseEntity::GetIsEntityActive() || !UIBaseEntity::GetIsRenderActive())
	{
		return;
	}

	//���N���X�̕`��
	UIBaseEntity::Render();

	m_enemyHPBase->Render();
	m_enemyHP->Render();
	m_enemyName->Render();


}


void BossEnemyHP::Notify(const Telegram<GamePlayMessageType>& telegram)
{

	switch (telegram.messageType)
	{
		case GamePlayMessageType::BOSS_DAMAGE:
			{

			float* ratio = static_cast<float*>(telegram.extraInfo);
				m_enemyHP->SetRenderRatio(*ratio);
				
				
				m_enemyHP->SetRenderRatio(*static_cast<float*>(telegram.extraInfo));

			}
			break;
		default:
			break;
	}

}


