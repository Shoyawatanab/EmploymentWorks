#pragma once
#include "GameBase/StateMachine/StateMachine.h"

class BirdEnemy;

enum class BirdEnemyState
{
	IDEL                                  //�ʏ�
	,MOVE                                 //����
	,BULLET_ATTACK						  //�r�[���U��
};


class BirdEnemyStateMachine : public StateMachine<IState, BirdEnemyState> 
{
public:
	//�R���X�g���N
	BirdEnemyStateMachine(BirdEnemy* birdEnemy);
	//�f�X�g���N�^
	~BirdEnemyStateMachine() override ;



};


