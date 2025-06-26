#pragma once
#include "GameBase/Action/ActionManager.h"
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Player;
class BossEnemy;
class BossEnemyBeam;

class BossEnemyActionManager : public ActionManager , public IObserver< SceneMessageType>
{
public:
	//�R���X�g���N�^
	BossEnemyActionManager(BossEnemy* ower,Player* target, BossEnemyBeam* beam);
	//�f�X�g���N�^
	~BossEnemyActionManager() override;

	//�ʒm���󂯎��֐�
	void Notify(SceneMessageType type, void* datas) override;

};