#pragma once
#ifndef ISUBJECT_DEFINED
#define ISUBJECT_DEFINED
#include "pch.h"

// ISubjectインターフェースを定義する
class ISubject
{
public:
	// デストラクタ
	virtual ~ISubject() = default;
	// 観察者をアタッチする
	virtual void Attach(std::string name,std::function<void> event) = 0;
	// 観察者をデタッチする
	virtual  void Detach(std::string name) = 0;
	// 通知する
	virtual void Notify(std::string name) = 0;
};

#endif	// ISUBJECT_DEFINED

