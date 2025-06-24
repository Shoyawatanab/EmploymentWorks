#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"

class BirdEnemy;

enum class BirdEnemyState
{
	IDEL                                  //�ʏ�
	,MOVE                                 //����
	,BEAM_ATTACK						  //�r�[���U��
};


class BirdEnemyStateMachine : public StateMachine<IState, BirdEnemyState> , public IObserver
{
public:
	//�R���X�g���N
	BirdEnemyStateMachine(BirdEnemy* birdEnemy);
	//�f�X�g���N�^
	~BirdEnemyStateMachine() override ;

	//�ʒm���ɌĂяo�����
	void Notify(MessageType type, void* datas) override;


};


