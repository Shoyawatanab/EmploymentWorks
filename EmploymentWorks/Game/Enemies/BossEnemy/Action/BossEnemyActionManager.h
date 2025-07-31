/*
	�N���X��     : BossEnemyActionManager
	����         : �{�X�G�̍s���̃}�l�[�W���[
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Action/ActionManager.h"
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Player;
class BossEnemy;
class BossEnemyBeam;

class BossEnemyActionManager : public ActionManager
{
public:
	//�R���X�g���N�^
	BossEnemyActionManager(BossEnemy* ower,Player* target, BossEnemyBeam* beam);
	//�f�X�g���N�^
	~BossEnemyActionManager() override;

	//�ʒm���󂯎��֐�
	void Notify(SceneMessageType type, void* datas);

private:
	//�{�X
	BossEnemy* m_bossEnemy;

};