#pragma once
#ifndef MESSENGER_DEFINED
#define MESSENGER_DEFINED

#include "Interface/ISubject.h"
#include <unordered_map>
#include <functional>


// Subjectクラスを定義する
class Messenger : public ISubject
{
public:
	// 観察者をアタッチする
	static void Attach(std::string name, std::function<void()> eventFunction);
	// 観察者をデタッチする
	static void Detach(std::string name);
	// 通知する
	static void Notify(std::string name);

private:

	static std::unordered_map<std::string, std::function<void()>> m_eventList;

public:

	//イベント名の変数

	//スロー演出
	static const std::string SLOWMOTION;

	static const std::string SLOWMOTIONEND;
};

#endif	// MESSENGER_DEFINED