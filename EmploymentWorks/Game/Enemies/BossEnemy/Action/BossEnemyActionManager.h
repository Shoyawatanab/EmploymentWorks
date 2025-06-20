#pragma once
#include "GameBase/Action/ActionManager.h"
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"

class Player;
class BossEnemy;

class BossEnemyActionManager : public ActionManager , public IObserver
{
public:
	//コンストラクタ
	BossEnemyActionManager(BossEnemy* ower,Player* target);
	//デストラクタ
	~BossEnemyActionManager() override;

	//通知を受け取る関数
	void Notify(MessageType type, void* datas) override;

};