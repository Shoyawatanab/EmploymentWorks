#pragma once
#include "GameBase/Action/ActionManager.h"
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"

class Player;
class BossEnemy;

class BossEnemyActionManager : public ActionManager , public IObserver
{
public:
	//�R���X�g���N�^
	BossEnemyActionManager(BossEnemy* ower,Player* target);
	//�f�X�g���N�^
	~BossEnemyActionManager() override;

	//�ʒm���󂯎��֐�
	void Notify(MessageType type, void* datas) override;

};