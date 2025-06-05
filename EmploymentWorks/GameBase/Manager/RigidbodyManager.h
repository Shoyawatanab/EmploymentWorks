#pragma once
#include "GameBase/Component/Rigidbody/RigidbodyComponent.h"


class RigidbodyManager
{

public:
	//�R���X�g���N�^
	RigidbodyManager();
	//�f�X�g���N�^
	~RigidbodyManager();

	//�X�V����
	void Update(const float& deltaTime);
	//���W�b�g�{�f�B�[�̒ǉ�
	void AddRigidbody(RigidbodyComponent* rigidbody);
	//���W�b�g�{�f�B�[�̍폜
	void RemoveRigidbody(RigidbodyComponent* rigidbody);

private:
	//���W�b�g�{�f�B�[�R���|�[�l���g
	std::vector<RigidbodyComponent*> m_rigidbody;

};