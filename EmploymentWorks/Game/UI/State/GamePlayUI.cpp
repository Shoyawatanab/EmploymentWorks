#include "pch.h"
#include "GamePlayUI.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/Enemys/EnemyManager.h"
#include "Game/Observer/Messenger.h"
#include "Libraries/WataLib/DamageCountUI.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
GamePlayUI::GamePlayUI()
	:
	m_commonResources{}
	,m_position{}
	,m_scale{}
	,m_rotation{}
	,m_player{}
	,m_playerHP{}
	,m_boomerang{}
	,m_windowSize{}
	,m_playerHPCount{}
	,m_boomerangCount{}
	,m_enemyHP{}
	,m_enemyHPBase{}
	, m_itemAcquisitionUI{}
	,m_throwUI{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
GamePlayUI::~GamePlayUI()
{
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void GamePlayUI::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{


	for (int i = 0; i < m_playerHPCount; i ++)
	{
		m_playerHP[i]->Render();
	}

	for (int i = 0; i < m_boomerangCount; i++)
	{
		m_boomerang[i]->Render();
	}

	if (m_enemyManager->GetBossEnemy() != nullptr)
	{
		for (auto& enemyHP : m_enemyHPBase)
		{
			enemyHP->Render();

		}

		m_enemyHP->Render();

	}

	for (auto& throwUI : m_throwUI)
	{
		throwUI->Render();
	}

	m_itemAcquisitionUI->Render();

	for (auto& da : m_damageCountUI)
	{
		da->Render(view,projection);
	}

}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="enemyManager">エネミーマネージャー</param>
void GamePlayUI::AddPointer(Player* player, EnemyManager* enemyManager)
{
	m_player = player;
	m_enemyManager = enemyManager;
}

/// <summary>
/// 画像の追加
/// </summary>
/// <param name="path">読み込みのパス</param>
/// <param name="position">座標</param>
/// <param name="scale">大きさ</param>
/// <param name="anchor">アンカー</param>
/// <param name="kind">種類</param>
/// <returns>UIのポインタ</returns>
std::unique_ptr<UserInterface> GamePlayUI::AddTexture(std::string key, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale)
{
	//  メニューとしてアイテムを追加する
	std::unique_ptr<UserInterface> userInterface = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	userInterface->Create(m_commonResources
		, key
		, position
		, scale
		);


	return userInterface;
}

/// <summary>
/// 敵HPの作成
/// </summary>
void GamePlayUI::CreateEnemyHP()
{

	m_enemyHPBase.push_back(AddTexture("BossHPBase"
		, ENEMY_HP_BASE_POSITION
		, ENEMY_HP_BASE_SCALE
		));

	m_enemyHP = AddTexture("EnemyHP"
		, ENEMY_HP_POSITION
		, ENEMY_HP_SCALE
		);

	m_enemyHPBase.push_back(AddTexture("EnemyName"
		, ENEMY_NAME_POSITION
		, ENEMY_NAME_SCALE
		));



}

/// <summary>
/// プレイヤHPの作成
/// </summary>
void GamePlayUI::CreatePlayerHP()
{

	for (int i = 0; i < HP_COUNT; i++)
	{
		auto texture = std::make_unique<UserInterface>();
		texture->Create(m_commonResources, "HP"
			, HP_POSITION + (HP_POSITION_OFFSET * static_cast<float>(i)), HP_SCALE);

		m_playerHP.push_back(std::move(texture));
	}

}

/// <summary>
/// ブーメラン残機の生成
/// </summary>
void GamePlayUI::CreateBoomerang()
{

	for (int i = 0; i < BOOMERANG_COUNT; i++)
	{
		auto texture = std::make_unique<UserInterface>();
		texture->Create(m_commonResources, "BoomerangUI"
			, BOOMERANG_POSITION + (BOOMERANG_POSITION_OFFSET * static_cast<float>(i)), BOOMERANG_SCALE);

		m_boomerang.push_back(std::move(texture));
	}


}

void GamePlayUI::CreateDamageUI(void* datas)
{

	UnknownDataThree* data = static_cast<UnknownDataThree*>(datas);


	for (auto& damageCount : m_damageCountUI)
	{
		if (!damageCount->GetIsActive())
		{
			damageCount->SetIsActive(true);

			damageCount->SetPosition(*static_cast<DirectX::SimpleMath::Vector3*>(data->data1));

			//damageCount->SetDamage(*static_cast<int*>(data->data3));
			damageCount->SetDamage(10);


			break;
		}
	}




}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void GamePlayUI::Initialize(CommonResources* resources)
{
	m_commonResources = resources;

	//画面サイズの取得
	m_windowSize.first = m_commonResources->GetDeviceResources()->GetOutputSize().right;
	m_windowSize.second = m_commonResources->GetDeviceResources()->GetOutputSize().bottom;

	m_playerHPCount = HP_COUNT;

	m_boomerangCount = BOOMERANG_COUNT;

	CreatePlayerHP();
	CreateBoomerang();
	CreateEnemyHP();

	m_itemAcquisitionUI = AddTexture("F"
		, Vector2(750, 600)
		, Vector2(0.15f, 0.15f)
		);

	m_itemAcquisitionUI->SetIsActive(false);

	m_throwUI.push_back(AddTexture("RightThrow"
		, RIGHT_THROW_POSITION
		, RIGHT_THROW_SCALE
		));

	m_throwUI.push_back(AddTexture("FrontThrow"
		, FRONT_THROW_POSITION
		, FRONT_THROW_SCALE
		));

	m_throwUI.push_back(AddTexture("LeftThrow"
		, LEFT_THROW_POSITION
		, LEFT_THROW_SCALE
		));

	m_throwUI[0]->SetPosition(m_throwUI[0]->GetInitialPosition() + MOVEPOSITION);


	for (int i = 0; i < MAXDAMAGEUICOUNT; i++)
	{
		auto dameUi = std::make_unique<WataLib::DamageCountUI>(m_commonResources);
		dameUi->Initialize();

		m_damageCountUI.push_back(std::move(dameUi));

	}

	Messenger::GetInstance()->Rigister(GameMessageType::BOOMERANG_THTROW, this);
	Messenger::GetInstance()->Rigister(GameMessageType::GET_BOOMERANG, this);
	Messenger::GetInstance()->Rigister(GameMessageType::PLAYER_DAMAGE, this);
	Messenger::GetInstance()->Rigister(GameMessageType::CHARGE_BOOMERANG_THROW_STATE, this);
	Messenger::GetInstance()->Rigister(GameMessageType::BOOMERANG_RECOVERBLE, this);
	Messenger::GetInstance()->Rigister(GameMessageType::BOOMERANG_NOT_RECOVERBLE, this);

	Messenger::GetInstance()->Rigister(GameMessageType::CREATE_HIT_EFFECT, this);

}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void GamePlayUI::Update(const float& elapsedTime)
{

	if (m_enemyManager->GetBossEnemy() != nullptr)
	{
		m_enemyHP->SetRenderRatio(m_enemyManager->GetBossHPRation());

	}


	for (auto& da : m_damageCountUI)
	{
		da->Update(elapsedTime);
	}

}

/// <summary>
/// 状態に入った時
/// </summary>
void GamePlayUI::Enter()
{



}

/// <summary>
/// 状態を抜けた時
/// </summary>
void GamePlayUI::Exit()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="datas">イベントのデータ</param>
void GamePlayUI::Notify(const Telegram<GameMessageType>& telegram)
{

	switch (telegram.messageType)
	{
		case GameMessageType::BOOMERANG_THTROW:
			m_boomerangCount--;

			m_boomerangCount = std::max(m_boomerangCount, 0);

			break;
		case GameMessageType::GET_BOOMERANG:
			m_boomerangCount++;
			m_boomerangCount = std::min(m_boomerangCount, BOOMERANG_COUNT);

			break;
		case GameMessageType::PLAYER_DAMAGE:
			m_playerHPCount--;
			break;
		case GameMessageType::CHARGE_BOOMERANG_THROW_STATE:
			{
				
				switch (*static_cast<int*>(telegram.extraInfo))
				{
					case 0:

						m_throwUI[0]->SetPosition(m_throwUI[0]->GetInitialPosition() + MOVEPOSITION);
						m_throwUI[1]->SetPosition(m_throwUI[1]->GetInitialPosition());
						m_throwUI[2]->SetPosition(m_throwUI[2]->GetInitialPosition());

						break;
					case 1:
						m_throwUI[0]->SetPosition(m_throwUI[0]->GetInitialPosition());
						m_throwUI[1]->SetPosition(m_throwUI[1]->GetInitialPosition() + MOVEPOSITION);
						m_throwUI[2]->SetPosition(m_throwUI[2]->GetInitialPosition());
						break;
					case 2:
						m_throwUI[0]->SetPosition(m_throwUI[0]->GetInitialPosition());
						m_throwUI[1]->SetPosition(m_throwUI[1]->GetInitialPosition());
						m_throwUI[2]->SetPosition(m_throwUI[2]->GetInitialPosition() + MOVEPOSITION);
						break;
					default:
						break;
				}
			}
			break;
		case GameMessageType::BOOMERANG_RECOVERBLE:
			m_itemAcquisitionUI->SetIsActive(true);
			break;
		case GameMessageType::BOOMERANG_NOT_RECOVERBLE:
			m_itemAcquisitionUI->SetIsActive(false);
			break;
		case GameMessageType::CREATE_HIT_EFFECT:
			CreateDamageUI(telegram.extraInfo);
			break;
		default:
			break;
	}
}




void GamePlayUI::PlayerDamage()
{
}







