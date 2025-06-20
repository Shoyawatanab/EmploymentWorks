/*
	ActionNode.h
	�n��Ė�
	�r�w�C�r�A�c���[�̎��s�݂̂̃m�[�h
	�q�������Ȃ�
*/

#pragma once
#include "Game/Interface/ILeafNode.h"
#include <functional>

class CommonResources;
class ExecutionNode;
class Player;
class Enemy;

class ActionNode : public ILeafNode
{
	
public:
	//�R���X�g���N�^
	ActionNode(std::function<IBehaviorNode::State(float)> fun);
	//�f�X�g���N�^
	~ActionNode() override;
	//������
	void Initialize()override;
	//�X�V
	IBehaviorNode::State Update(const float& deltaTime) override;

	void Finalize()override;

private:

	//�֐���o�^����ϐ�
	std::function<IBehaviorNode::State(float)> m_executionNode;


};
/*����
  
  �֐��̓o�^�ϐ��́ifloat�j�������Ă��邯�Ǔo�^����֐��Ɉ������Ȃ��Ă�����ɓ����Ă���̂œ�
  ()��(float)�̂Q�����Ȃ��Ƃ����Ȃ��Ǝv�������ǂ����Ă��܂���
  BehaviorTree�N���X�ň������K�v�Ȋ֐��ɂ�std::placeholders::_1�����Ă���

�@Update��RunningUpdate�����g�������Ȃ̂Œ�������
 �@�������s���m�[�h������Ȃ�RunningUpdate�ɓ�����Update�͌Ă΂�Ȃ�
*/