#pragma once
#include <any>
#include <unordered_map>
#include <string>


#include "Libraries/WataLib/Singleton.h"
#include <fstream>



class InstanceRegistry : public Singleton<InstanceRegistry>
{

public:
	//�R���X�g���N�^
	InstanceRegistry() = default;

	/// <summary>
	/// �o�^
	/// </summary>
	/// <typeparam name="T">�N���X</typeparam>
	/// <param name="name">���O</param>
	/// <param name="instance">�o�^�N���X</param>
	template<typename T>
	void Register(const std::string& name, T* instance)
	{
		m_registry[name] = instance;
	}

	/// <summary>
	/// �o�^���ꂽ�N���X�̎擾
	/// </summary>
	/// <typeparam name="T">�擾�������N���X</typeparam>
	/// <param name="name">�擾�������O</param>
	/// <returns>�o�^���ꂽ�N���X</returns>
	template<typename T>
	T* GetRegistryInstance(const std::string& name)
	{
		return std::any_cast<T*>(m_registry.at(name));
	}

	/// <summary>
	/// �o�^��̃N���A
	/// </summary>
	void RegistryClear()
	{
		m_registry.clear();
	}

private:

	//�o�^��
	std::unordered_map<std::string, std::any> m_registry;

};