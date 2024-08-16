/*
	ActionNode.h
	�n��Ė�
	�r�w�C�r�A�c���[�̎��s�݂̂̃m�[�h
	�q�������Ȃ�
*/

#pragma once
#include "Interface/ILeafNode.h"
#include <functional>

class CommonResources;
class ExecutionNode;
class Player;
class Enemy;

class ActionNode : public ILeafNode
{




private:
	//CommonResources* m_commonResources;

	//�֐���o�^����ϐ�
	std::function<IBehaviorNode::State(float)> m_executionNode;
	
public:
	ActionNode(std::function<IBehaviorNode::State(float)> fun);
	~ActionNode() override;

	void Initialize()override;
	IBehaviorNode::State Update(float elapsedTime) override;
	IBehaviorNode::State RunningUpdate(float elapsedTime) override;


	void Render();
	void Finalize()override;



};
/*����
  
  �֐��̓o�^�ϐ��́ifloat�j�������Ă��邯�Ǔo�^����֐��Ɉ������Ȃ��Ă�����ɓ����Ă���̂œ�
  ()��(float)�̂Q�����Ȃ��Ƃ����Ȃ��Ǝv�������ǂ����Ă��܂���
  BehaviorTree�N���X�ň������K�v�Ȋ֐��ɂ�std::placeholders::_1�����Ă���

�@Update��RunningUpdate�����g�������Ȃ̂Œ�������
 �@�������s���m�[�h������Ȃ�RunningUpdate�ɓ�����Update�͌Ă΂�Ȃ�
*/