#pragma once
#ifndef ISUBJECT_DEFINED
#define ISUBJECT_DEFINED
#include "pch.h"

// ISubject�C���^�[�t�F�[�X���`����
class ISubject
{
public:
	// �f�X�g���N�^
	virtual ~ISubject() = default;
	// �ώ@�҂��A�^�b�`����
	virtual void Attach(std::string name,std::function<void> event) = 0;
	// �ώ@�҂��f�^�b�`����
	virtual  void Detach(std::string name) = 0;
	// �ʒm����
	virtual void Notify(std::string name) = 0;
};

#endif	// ISUBJECT_DEFINED

