/*
* コンポジットパターンの根のインターフェース
*/
#pragma once
#include "Game/Interface/ICompositeRoot.h"

class EnemyManager;

class IEnemy : public ICompositeRoot
{
public:
	//デストラクタ
	virtual ~IEnemy() = default;

	virtual void SetManager(EnemyManager* enemyManager) = 0;

	virtual bool GetIsActives() = 0;

};
