
#include "pch.h"
#include "Game/Object/BirdEnemy/State/BirdEnemyIdling.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Observer/Messenger.h"

const float MOVE_SPEED = 5.0f;                                        //動く時のスピード
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION(0.0f, 0.0f, -1.0f); //初期の向いている方向


// コンストラクタ
BirdEnemyldling::BirdEnemyldling()
	:
	m_commonResources{},
	m_player{}
	,m_graivty{}
{



}

// デストラクタ
BirdEnemyldling::~BirdEnemyldling()
{

}

// 初期化する
void BirdEnemyldling::Initialize()
{
	m_graivty = 0.0f;
}


// 更新する
void BirdEnemyldling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;





}


void BirdEnemyldling::Enter()
{

}

void BirdEnemyldling::Exit()
{

}

void BirdEnemyldling::RegistrationInformation(CommonResources* resoure, Player* player, BirdEnemy* birdEnemy)
{
	m_commonResources = resoure;
	m_player = player;
	m_birdEnemy = birdEnemy;

}

