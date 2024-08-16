#include "pch.h"
#include "Game/BehaviorTree/Conditions.h"
#include "Conditions.h"

#include "Game/Object/Player.h"
#include "Game/Object/Enemy/Enemy.h"

Conditions::Conditions(Player* player, Enemy* enemy)
	:
	m_palyer{player},
	m_enemy{enemy}
{

}

Conditions::~Conditions()
{

}



/// <summary>
/// �v���C�����ǂꂾ���ǂ���������
/// </summary>
/// <returns>���l�𒴂��Ă���:true�A�����Ă��Ȃ�:false</returns>
bool Conditions::ChasingDistance()
{

	return false ;
}


/// <summary>
/// ��]�ł��邩�ǂ���
/// </summary>
/// <returns>��]�ł���Ftrue�A�ł��Ȃ�:false</returns>
bool Conditions::IsRotation()
{



	return false;
}

/// <summary>
/// �v���C�������������ǂ���
/// </summary>
/// <returns>���ĂȂ�:false ,������:true</returns>
bool Conditions::FindToPlayer()
{

	DirectX::SimpleMath::Vector3 Distance = m_palyer->GetPos() - m_enemy->GetPos();

	//�������T�ȓ��Ȃ�
	if (Distance.Length() <= 5)
	{
		return false;
	}

	//�����ĂȂ��@����ɍs���Ăق�������
	return true;
}


