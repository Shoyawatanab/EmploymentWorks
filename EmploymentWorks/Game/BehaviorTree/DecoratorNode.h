/*
	DecoratorNode.h
	�n��Ė�
	�r�w�C�r�A�c���[�̏�������̃m�[�h
	������ʂ�Ύq�̃X�e�[�g��Ԃ�
	�@�@�@�ʂ�Ȃ����Failure��Ԃ�
*/
#pragma once
#include "Interface/ICompositeNode.h"

class CommonResources;


class DecoratorNode : public ICompositeNode
{




private:
	//CommonResources* m_commonResources;

	//�q�m�[�h�z��
	std::unique_ptr<IBehaviorNode> m_childNode;


	//�֐���o�^����ϐ�
	std::function<bool()> m_condition;


public:
	DecoratorNode(std::function<bool()> fun);
	~DecoratorNode() override;

	void Initialize() override;
	IBehaviorNode::State Update(float elapsedTime) override;
	IBehaviorNode::State RunningUpdate(float elapsedTime) override;

	void Render();
	void Finalize() override ;

	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;

	void AddConditions();

}; 

/*����
�@Update��RunningUpdate�����g�������Ȃ̂Œ�������
 �@�������s���m�[�h������Ȃ�RunningUpdate�ɓ�����Update�͌Ă΂�Ȃ�
*/