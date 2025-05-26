#pragma once
#include <any>
#include <unordered_map>
#include <string>


#include "Libraries/WataLib/Singleton.h"
#include <fstream>



class InstanceRegistry : public Singleton<InstanceRegistry>
{

public:
	//コンストラクタ
	InstanceRegistry() = default;

	/// <summary>
	/// 登録
	/// </summary>
	/// <typeparam name="T">クラス</typeparam>
	/// <param name="name">名前</param>
	/// <param name="instance">登録クラス</param>
	template<typename T>
	void Register(const std::string& name, T* instance)
	{
		m_registry[name] = instance;
	}

	/// <summary>
	/// 登録されたクラスの取得
	/// </summary>
	/// <typeparam name="T">取得したいクラス</typeparam>
	/// <param name="name">取得した名前</param>
	/// <returns>登録されたクラス</returns>
	template<typename T>
	T* GetRegistryInstance(const std::string& name)
	{
		return std::any_cast<T*>(m_registry.at(name));
	}

	/// <summary>
	/// 登録簿のクリア
	/// </summary>
	void RegistryClear()
	{
		m_registry.clear();
	}

private:

	//登録簿
	std::unordered_map<std::string, std::any> m_registry;

};