/*
	DecoratorNode.h
	�n��Ė�
	�r�w�C�r�A�c���[�̏�������̃m�[�h
	������ʂ�Ύq�̃X�e�[�g��Ԃ�
	�@�@�@�ʂ�Ȃ����Failure��Ԃ�
*/
#pragma once
#include "Game/Interface/ICompositeNode.h"

class CommonResources;


class DecoratorNode : public ICompositeNode
{

public:
	//�R���X�g���N�^
	DecoratorNode(std::function<bool(float)> fun);
	//�f�X�g���N�^
	~DecoratorNode() override;
	//������
	void Initialize() override;
	//�X�V
	IBehaviorNode::State Update(const float& deltaTime) override;

	void Finalize() override ;
	//�q�m�[�h�̎��s
	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;

private:

	//�q�m�[�h�z��
	std::unique_ptr<IBehaviorNode> m_childNode;


	//�֐���o�^����ϐ�
	std::function<bool(float)> m_condition;


}; 

/*����
�@Update��RunningUpdate�����g�������Ȃ̂Œ�������
 �@�������s���m�[�h������Ȃ�RunningUpdate�ɓ�����Update�͌Ă΂�Ȃ�
*/