/*
* �v���C���N���X�@
*/

#pragma once


template<typename T>
class Singleton
{
public:

	static T* GetInstance()
	{
		if (instance == nullptr)
		{
			instance.reset(new T());
		}
		return instance.get();
	}

public:
	
	// �R�s�[�E���[�u�֎~
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
	
	Singleton() = default;

private:

	//
	static std::unique_ptr<T> instance;

};


template<typename T> 
std::unique_ptr<T> Singleton<T>::instance = nullptr;
