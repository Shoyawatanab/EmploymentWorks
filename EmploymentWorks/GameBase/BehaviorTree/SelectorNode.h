/*
	SelectorNode.h
	�n��Ė�
	�r�w�C�r�A�c���[�̃m�[�h
	��������q��������܂Ŏq�����s����
	����������Success��Ԃ�
	������Ȃ���Failure��Ԃ�
*/#pragma once
#include "Game/Interface/ICompositeNode.h"

class CommonResources;


class SelectorNode : public ICompositeNode
{

public:
	//�R���X�g���N�^
	SelectorNode();
	//�f�X�g���N�^
	~SelectorNode() override;
	//������
	void Initialize() override;
	//�X�V
	IBehaviorNode::State Update(const float& deltaTime) override;

	void Finalize()override;
	//�m�[�h�̒ǉ�
	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;

private:
	//�q�m�[�h�z��
	std::vector<std::unique_ptr<IBehaviorNode>> m_childNode;


}; 
