/*
	SequenceNode.h
	�n��Ė�
	�r�w�C�r�A�c���[�̃m�[�h
	���ԂɎq�����s����
	�S�Ă̎q�����s�ł����Success
	�q�����s�����炷����Failure�𔽂�
*/
#pragma once
#include "Game/Interface/ICompositeNode.h"


class CommonResources;


class SequenceNode : public ICompositeNode
{

public:
	//�R���X�g���N�^
	SequenceNode();
	//�f�X�g���N�^
	~SequenceNode()  override;
	//������
	void Initialize() override;
	//�X�V
	IBehaviorNode::State Update(const float& deltaTime) override;

	void Finalize() override;
	//�m�[�h�̒ǉ�
	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;
private:
	//�q�m�[�h�z��
	std::vector<std::unique_ptr<IBehaviorNode>> m_childNode;


};