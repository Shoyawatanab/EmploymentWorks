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
	// 観察者をアタッチする
	static void Attach2(std::string name, std::function<void(DirectX::SimpleMath::Vector3)> eventFunction);

	// 観察者をデタッチする
	static void Detach(std::string name);
	// 通知する
	static void Notify(std::string name);
	// 通知する
	static void Notify2(std::string name,DirectX::SimpleMath::Vector3 pos);

private:



	static std::unordered_map<std::string, std::function<void()>> m_eventList;

	static std::unordered_map<std::string, std::function<void(DirectX::SimpleMath::Vector3)>> m_eventList2;

public:

	//イベント名の変数

	//スロー演出
	static const std::string SLOWMOTION;

	static const std::string SLOWMOTIONEND;
	
	static const std::string CREATEHITEFFECTS;
};

#endif	// MESSENGER_DEFINED


//引数が違う分だけNotifyなどがあるからテンプレートなどを使って一つにしたい




