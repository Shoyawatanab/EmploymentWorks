/*
* �R���|�W�b�g�̌��ƂȂ�N���X�̃C���^�[�t�F�[�X
*/
#pragma once
#include "Game/Interface/IComposite.h"
#include "Libraries/WataLib/Json.h"

class ICompositeRoot : public IComposite
{
public:
	//�f�X�g���N�^
	virtual ~ICompositeRoot() = default;

	virtual void Damage(int damage) = 0;

};
