/*
	Root.h
	�n��Ė�
	�r�w�C�r�A�c���[�̃m�[�h
	���ԂɎq�����s����
	�S�Ă̎q�����s�ł����Success
	�q�����s�����炷����Failure�𔽂�
*/
#pragma once
#include "Interface/ICompositeNode.h"


class CommonResources;


class Root : public ICompositeNode
{




private:
	//CommonResources* m_commonResources;

	//�q�m�[�h�z��
	std::unique_ptr<IBehaviorNode> m_childNode;


public:
	Root();
	~Root() override;

	void Initialize() override;
	IBehaviorNode::State Update(float elapsedTime) override;
	IBehaviorNode::State RunningUpdate(float elapsedTime) override;

	void Render();
	void Finalize() override;

	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;


};