
#include "pch.h"
#include "Game/Object/BirdEnemy/State/BirdEnemyUsually.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Object/BirdEnemy/BirdEnemy.h"

const float MOVE_SPEED = 5.0f;                                        //動く時のスピード
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION(0.0f, 0.0f, -1.0f); //初期の向いている方向


// コンストラクタ
BirdEnemyUsually::BirdEnemyUsually()
	:
	m_commonResources{},
	m_player{}
{



}

// デストラクタ
BirdEnemyUsually::~BirdEnemyUsually()
{

}

// 初期化する
void BirdEnemyUsually::Initialize()
{
}


// 更新する
void BirdEnemyUsually::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;



}


void BirdEnemyUsually::Enter()
{

}

void BirdEnemyUsually::Exit()
{

}

void BirdEnemyUsually::RegistrationInformation(CommonResources* resoure,Player* player, BirdEnemy* birdEnemy)
{
	m_commonResources = resoure;
	m_player = player;
	m_birdEnemy = birdEnemy;

}

void BirdEnemyUsually::Move(float elapsedTime,  DirectX::SimpleMath::Vector3 moveDirection)
{

}


void BirdEnemyUsually::Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection)
{

	UNREFERENCED_PARAMETER(elapsedTime);
	UNREFERENCED_PARAMETER(moveDirection);
	using namespace DirectX::SimpleMath;



}
