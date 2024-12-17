
#include "pch.h"
#include "Game/Object/BirdEnemy/State/BirdEnemyAttack.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Observer/Messenger.h"
#include "Game/Object/BirdEnemy/BirdEnemy.h"

const float MOVE_SPEED = 5.0f;                                        //動く時のスピード
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION(0.0f, 0.0f, -1.0f); //初期の向いている方向


// コンストラクタ
BirdEnemyAttack::BirdEnemyAttack()
	:
	m_player{}
	,m_graivty{}
{



}

// デストラクタ
BirdEnemyAttack::~BirdEnemyAttack()
{

}

// 初期化する
void BirdEnemyAttack::Initialize()
{
	m_graivty = 0.0f;
}


// 更新する
void BirdEnemyAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;



	Vector3 pos = m_birdEnemy->GetPosition();

	pos.y += 1.0f * elapsedTime;

	m_birdEnemy->SetPosition(pos);


}


void BirdEnemyAttack::Enter()
{

}

void BirdEnemyAttack::Exit()
{

}

void BirdEnemyAttack::RegistrationInformation(CommonResources* resoure, Player* player, BirdEnemy* birdEnemy)
{
	m_commonResources = resoure;
	m_player = player;
	m_birdEnemy = birdEnemy;
}

void BirdEnemyAttack::Attack(float elapsedTime, DirectX::Keyboard::State key)
{

	using namespace DirectX;
	UNREFERENCED_PARAMETER(elapsedTime);
	UNREFERENCED_PARAMETER(key);

	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();





}

