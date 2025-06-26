/*
�Q�[���S�̂̃��b�Z���W���[�N���X

*/
#pragma once
#include "Libraries/WataLib/Singleton.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Global/GlobalMeesageType.h"
#include <unordered_map>


class GlobalMessenger : public Singleton<GlobalMessenger>
{
	friend class Singleton<GlobalMessenger>;
public:

	//�R���X�g���N
	GlobalMessenger();
	//�f�X�g���N�^
	~GlobalMessenger() override;

	//���X�g�ɓo�^
	void Rigister(std::vector<GlobalMessageType> types, IObserver<GlobalMessageType>* observer);
	//�ʒm
	void Notify(GlobalMessageType type, void* datas = nullptr);
	//�N���A
	void Clear();

private:

	std::unordered_map<GlobalMessageType, std::vector<IObserver<GlobalMessageType>*>> m_list;


};