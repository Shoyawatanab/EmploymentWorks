#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"


class BirdEnemyBullet;
class BirdEnemy;

enum class BirdEnemyBulletState
{
	IDEL                                  //�ʏ�
	,CHAGE                                //�`���[�W
	,SHOT						          //�V���b�g
};


class BirdEnemyBulletStateMachine : public StateMachine<IState, BirdEnemyBulletState> , public IObserver
{
public:
	//�R���X�g���N
	BirdEnemyBulletStateMachine(BirdEnemyBullet* bullet, BirdEnemy* birdEnemy);
	//�f�X�g���N�^
	~BirdEnemyBulletStateMachine() override ;

	//�ʒm���ɌĂяo�����
	void Notify(MessageType type, void* datas) override;


};


