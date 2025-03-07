/*
* �R���|�W�b�g�p�^�[���̍��̃C���^�[�t�F�[�X
*/
#pragma once
#include "Game/Interface/ICharacter.h"


class IComposite : public ICharacter
{
public:
	//�f�X�g���N�^
	virtual ~IComposite() = default;
	//�q�v�f�̒ǉ�
	virtual void AddChild(std::unique_ptr<ICharacter> parts) = 0;
	//�q�v�f�̍폜
	//virtual void DeleteChild(std::unique_ptr<ICharacter> parts) = 0;
};
