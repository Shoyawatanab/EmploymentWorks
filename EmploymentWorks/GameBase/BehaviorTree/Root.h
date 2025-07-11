/*
	�N���X��     : Root
	����         : �r�w�C�r�A�c���[�̃��[�g�m�[�h
	�⑫�E���ӓ_ :�@���ԂɎq�����s����B�S�Ă̎q�����s�ł����Success�A�q�����s�����炷����Failure�𔽂�
*/
#pragma once
#include "Game/Interface/ICompositeNode.h"


class CommonResources;


class Root : public ICompositeNode
{


public:
	//�R���X�g���N�^
	Root();
	//�f�X�g���N�^
	~Root() override;
	//������
	void Initialize() override;
	//�X�V
	IBehaviorNode::State Update(const float& deltaTime) override;

	void Finalize() override;
	//�m�[�h�̒ǉ�
	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;

private:

	//�q�m�[�h�z��
	std::unique_ptr<IBehaviorNode> m_childNode;


};