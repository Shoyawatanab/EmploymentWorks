#include "pch.h"
#include "Game/BehaviorTree/Conditions.h"
#include "Conditions.h"

#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/CommonResources.h"


Conditions::Conditions(CommonResources* resources, Player* player, Enemy* enemy)
	:
	m_commonResources{ resources },
	m_palyer{ player },
	m_enemy{ enemy },
	m_attackCoolTime{}
{

}

Conditions::~Conditions()
{

}



/// <summary>
/// ƒvƒŒƒCƒ„‚ğŒ©‚Â‚¯‚½‚©‚Ç‚¤‚©
/// </summary>
/// <returns>Œ©‚Â‚Ä‚È‚¢:true ,Œ©‚Â‚¯‚½:false</returns>
bool Conditions::IsFindToPlayer()
{
	//‹–ìŠpŠO
	if (!m_commonResources->GetJudgement()->IsWithinTheSector(m_palyer->GetPosition(), m_enemy->Getforward(), m_enemy->GetPosition(), 20, 90))
	{
		//„‰ñ‚És‚Á‚Ä‚Ù‚µ‚©‚çŒ©‚Â‚¯‚Ä‚¢‚È‚¢‚Æ‚«‚Étrue
		return true;
	}

	//Ray‚Ì‚½‚ß‚Ì•ûŒüƒxƒNƒgƒ‹‚Ìì¬
	DirectX::SimpleMath::Vector3 Direction = m_palyer->GetPosition() - m_enemy->GetPosition();
	//³‹K‰»
	Direction.Normalize();

	//Ray‚Ìì¬
	DirectX::SimpleMath::Ray ray;
	ray.position = m_enemy->GetPosition();
	//Ray‚Ìdirection‚Í³‹K‰»‚³‚ê‚Ä‚¢‚é‚±‚Æ
	ray.direction = Direction;


	//áŠQ•¨‚ª‚ ‚é‚©‚Ç‚¤‚©
	if (m_commonResources->GetJudgement()->IsRayToBoundingBox(ray, 1000))
	{
		return true;
	}

	//UŒ‚‚È‚Ç‚Ìƒm[ƒh‚És‚­
	return false;
}

/// <summary>
/// Hp‚ª”¼•ªˆÈã‚©‚Ç‚¤‚©
/// </summary>
/// <returns></returns>
bool Conditions::IsMoreThanHalfHP()
{

	if (m_commonResources->GetJudgement()->GetRatio(m_enemy->GetHp(), m_enemy->GetMAXHp()) >= 0.5f)
	{
		//”¼•ªˆÈã
		return true;
	}

	//”¼•ª–¢–
	return false;
}

//UŒ‚‚·‚é‚©‚Ç‚¤‚©
bool Conditions::IsAttack(float elapsdTime)
{

	//‚T•b‚Éˆê‰ñUŒ‚
	if (m_attackCoolTime >= 5)
	{
		//‚Ç‚Á‚©‚ÅƒN[ƒ‹ƒ^ƒCƒ€‚ÌƒŠƒZƒbƒg‚ª•K—v
		m_attackCoolTime = 0;
		m_enemy->RegistrationRungingAnimation("Beam");

		//UŒ‚
		return true;
	}



	m_attackCoolTime += elapsdTime;
	//UŒ‚‚µ‚È‚¢
	return false;
}

/// <summary>
/// ‹ß‹——£UŒ‚‚©‚Ç‚¤‚©
/// </summary>
/// <returns></returns>
bool Conditions::IsCloseRangeAttack()
{

	//if (m_commonResources->GetJudgement()->GetLenght(m_palyer->GetPos(), m_enemy->GetPos()) <= 7)
	//{
	//	//‹ß‹——£UŒ‚
	//	return true;
	//}

	//‰“‹——£UŒ‚
	return false;
}


