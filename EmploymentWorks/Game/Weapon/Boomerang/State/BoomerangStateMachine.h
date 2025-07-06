#pragma once
#include "GameBase/StateMachine/StateMachine.h"

class Boomerang;
class Player;

enum class BoomerangState
{
	IDEL                //�ʏ�
	,THROW				//�������Ă���
	,GET_READY			//�\���Ă���
	,BOUNCE				//���˕Ԃ�
	,DORP               //������
};

class BoomerangStateMachine : public StateMachine<IState, BoomerangState>
{

public:
	//�R���X�g���N�^
	BoomerangStateMachine(Boomerang* boomrang, Player* player);
	//�f�X�g���N�^
	~BoomerangStateMachine() override;

	//�h�����ChangeState���̏���
	void DerivationChangeState(BoomerangState state);

private:

	Boomerang* m_boomerang;

};
