#include "pch.h"
#include "Game/BehaviorTree/ExecutionNode.h"
#include "ExecutionNode.h"

#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/CommonResources.h"


static const float ROTATESPEED = 1.0f;
static const float PATROLSPEED = 2.0f;;


ExecutionNode::ExecutionNode(Player* player, Enemy* enemy)
	:
	m_palyer{ player },
	m_enemy{ enemy }
{

}

ExecutionNode::~ExecutionNode()
{

}

void ExecutionNode::Initialize(CommonResources* resources)
{

	m_commonResources = resources;
	CreatePatrol();


}

void ExecutionNode::CreatePatrol()
{

	//ƒpƒgƒ[ƒ‹À•W‚Ì¶¬
	//0.“G‚Ì‰Šú’n“_
	auto Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(0, 5.75f, -10);
	m_patrolPoint.push_back(std::move(Pointo));
	//1.¶ã
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(-16, 5.75f, -14);
	m_patrolPoint.push_back(std::move(Pointo));
	//2.¶
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(-27, 5.75f, 0);
	m_patrolPoint.push_back(std::move(Pointo));
	//3.¶‰º
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(-16, 5.75f, 14);
	m_patrolPoint.push_back(std::move(Pointo));
	//4.ƒvƒŒƒCƒ„‚Ì‰Šú’n“_
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(0, 2.75f, 10);
	m_patrolPoint.push_back(std::move(Pointo));
	//5.‰E‰º
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(16, 5.75f, 14);
	m_patrolPoint.push_back(std::move(Pointo));
	//6.‰E
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(27, 5.75f, 0);
	m_patrolPoint.push_back(std::move(Pointo));
	//7.‰Eã
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(16, 5.75f, -14);
	m_patrolPoint.push_back(std::move(Pointo));


	//—×Úƒ|ƒCƒ“ƒg‚Ì“o˜^
	//0‚É“o˜^
	m_patrolPoint.at(0)->SetAdjacentPosint(1, m_patrolPoint[1].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(6, m_patrolPoint[6].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(7, m_patrolPoint[7].get());
	//1‚É“o˜^
	m_patrolPoint.at(1)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(1)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(1)->SetAdjacentPosint(7, m_patrolPoint[7].get());
	//2‚É“o˜^
	m_patrolPoint.at(2)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(2)->SetAdjacentPosint(1, m_patrolPoint[1].get());
	m_patrolPoint.at(2)->SetAdjacentPosint(3, m_patrolPoint[3].get());
	m_patrolPoint.at(2)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	//3‚É“o˜^
	m_patrolPoint.at(3)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(3)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(3)->SetAdjacentPosint(5, m_patrolPoint[5].get());
	//4‚É“o˜^
	m_patrolPoint.at(4)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(5, m_patrolPoint[5].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(6, m_patrolPoint[6].get());
	//5‚É“o˜^
	m_patrolPoint.at(5)->SetAdjacentPosint(3, m_patrolPoint[3].get());
	m_patrolPoint.at(5)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(5)->SetAdjacentPosint(6, m_patrolPoint[6].get());
	//6‚É“o˜^
	m_patrolPoint.at(6)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(6)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(6)->SetAdjacentPosint(5, m_patrolPoint[5].get());
	m_patrolPoint.at(6)->SetAdjacentPosint(7, m_patrolPoint[7].get());
	//7‚É“o˜^
	m_patrolPoint.at(7)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(7)->SetAdjacentPosint(1, m_patrolPoint[1].get());
	m_patrolPoint.at(7)->SetAdjacentPosint(6, m_patrolPoint[6].get());


	//‰Šú’n“_‚ª0‚¾‚©‚ç
	m_currentPointNumber = 0;
	DecideNextPosition();
}

/// <summary>
/// Ÿ‚ÌÀ•W‚ğŒˆ‚ß‚é
/// </summary>
void ExecutionNode::DecideNextPosition()
{

	//—×Ú‚Ì”‚ğ‹‚ß‚é
	int size = m_patrolPoint.at(m_currentPointNumber)->m_adjacentNumber.size() - 1;
	//ƒ|ƒCƒ“ƒg‚Ì—×Ú”Ô†‚Ì”‚ğ‚à‚Æ‚Éƒ‰ƒ“ƒ_ƒ€‚Å”Ô†‚Ì¶¬
	int number = m_commonResources->GetJudgement()->GetRandom(0, size);
	//”Ô†‚ğ‚à‚Æ‚ÉŸ‚Ì—×Ú‚Ì”Ô†‚ğ‹‚ß‚é	
	number = m_patrolPoint.at(m_currentPointNumber)->GetAdjacentNumber(number);

	//number = 4;

	//I—¹’n“_‚ÉÀ•W‚ğ‘ã“ü‚·‚é
	m_endPatrolPos = m_patrolPoint.at(m_currentPointNumber)->GetAdjacentPointo(number)->Position;
	//Ÿ‚Ì”Ô–_‚Ì“o˜^
	m_nextPointNumber = number;


}


/// <summary>
/// „‰ñƒm[ƒh
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::Patrol(float elapsdTime)
{
	DirectX::SimpleMath::Vector3 EnemyPos = m_enemy->GetPos();

	//i‚Ş•ûŒü‚ğ‹‚ß‚é
	DirectX::SimpleMath::Vector3 MoveDirection = m_endPatrolPos - EnemyPos;
	MoveDirection.Normalize();

	MoveDirection *= PATROLSPEED * elapsdTime;

	EnemyPos += MoveDirection;

	m_enemy->SetPos(EnemyPos);

	//‹——£‚ğ‹‚ß‚é
	float distance = (m_endPatrolPos - EnemyPos).Length();


	if (distance <= 2.5f)
	{
		//Ÿ‚ÌÀ•W‚ğ
		m_currentPointNumber = m_nextPointNumber;
		DecideNextPosition();
	}


	//•ûŒü“]Š·
	//¡‚Ì“G‚Ì‘O•ûŒü
	DirectX::SimpleMath::Vector3 forward = m_enemy->Getforward();

	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(MoveDirection);

	if (moveAxis.y >= 0.0f)
	{
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//Šp“x‚ğ‹‚ß‚é
	float moveAngle = forward.Dot(MoveDirection);


	//ƒ‰ƒWƒAƒ“’l‚É•ÏŠ·
	moveAngle = acosf(moveAngle);

	//Šp“x‚Æ‘¬“x‚Ì”äŠr‚Å¬‚³‚¢‚Ù‚¤‚ğæ“¾
	moveAngle = std::min(moveAngle, ROTATESPEED * elapsdTime);

	//“G‚Ì‰ñ“]‚Ìæ“¾
	DirectX::SimpleMath::Quaternion Rotate = m_enemy->GetRotate();
	//Y²‚É‘Î‚µ‚Ä‰ñ“]‚ğ‚©‚¯‚é
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_enemy->SetRotate(Rotate);

	//‰ñ“]‚ğ‚à‚Æ‚É“G‚Ì‰Šú‚Ì•ûŒüƒxƒNƒgƒ‹‚ÌXV
	forward = DirectX::SimpleMath::Vector3::Transform(Enemy::INITIALFORWARD, Rotate);
	forward.Normalize();
	m_enemy->Setforward(forward);



	return IBehaviorNode::State::Success;
}



/// <summary>
/// ƒvƒŒƒCƒ„‚Ì‚Ù‚¤‚ÉŒü‚­
/// </summary>
/// <returns>true:¬Œ÷ , false:¸”s</returns>
IBehaviorNode::State ExecutionNode::FacingThePlayer(float elapsdTime)
{
	//Œü‚«‚½‚¢•ûŒü
	DirectX::SimpleMath::Vector3 direction = m_palyer->GetPos() - m_enemy->GetPos();
	direction.Normalize();
	//¡‚Ì“G‚Ì‘O•ûŒü
	DirectX::SimpleMath::Vector3 forward = m_enemy->Getforward();
	//forward.Normalize();



	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//Šp“x‚ğ‹‚ß‚é
	float moveAngle = forward.Dot(direction);

	//if (moveAngle < 0.01f)
	//{
	//	return IBehaviorNode::State::Failure;
	//}

//ƒ‰ƒWƒAƒ“’l‚É•ÏŠ·
	moveAngle = acosf(moveAngle);

	//Šp“x‚Æ‘¬“x‚Ì”äŠr‚Å¬‚³‚¢‚Ù‚¤‚ğæ“¾
	moveAngle = std::min(moveAngle, ROTATESPEED * elapsdTime);

	//“G‚Ì‰ñ“]‚Ìæ“¾
	DirectX::SimpleMath::Quaternion Rotate = m_enemy->GetRotate();
	//Y²‚É‘Î‚µ‚Ä‰ñ“]‚ğ‚©‚¯‚é
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_enemy->SetRotate(Rotate);

	//‰ñ“]‚ğ‚à‚Æ‚É“G‚Ì‰Šú‚Ì•ûŒüƒxƒNƒgƒ‹‚ÌXV
	forward = DirectX::SimpleMath::Vector3::Transform(Enemy::INITIALFORWARD, Rotate);
	forward.Normalize();
	m_enemy->Setforward(forward);

	return IBehaviorNode::State::Success;
}

/// <summary>
/// ‹ß‹——£UŒ‚
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::CloseRangeAttacks(float elapsdTime)
{
	return IBehaviorNode::State::Success;
}

/// <summary>
/// ‰“‹——£UŒ‚
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::RangedAttack(float elapsdTime)
{

	//‰“‹——£UŒ‚‚ÍRender‚ÌŠÖŒW‚ÅEnemyƒNƒ‰ƒX‚Åì‚Á‚½BeamAttack‚ğg—p‚µ‚Ä‚¢‚é



	//UŒ‚’†
	return IBehaviorNode::State::Runngin;
}

/// <summary>
/// ‰½‚à‚µ‚È‚¢
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::DoNothing()
{
	return IBehaviorNode::State::Success;
}

/// <summary>
/// “¦‚°‚é
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::RunAway(float elapsdTime)
{
	return IBehaviorNode::State::Success;
}

