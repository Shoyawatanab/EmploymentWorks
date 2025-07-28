/*
	�N���X��     : GlobalMessenger
	����         : �V�[�����܂���Messenger
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/WataLib/Singleton.h"
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
	//���X�g����폜
	void Delete(IObserver<GlobalMessageType>* observer);
	//�ʒm
	void Notify(GlobalMessageType type, void* datas = nullptr);
	//�N���A
	void Clear();

private:

	std::unordered_map<GlobalMessageType, std::vector<IObserver<GlobalMessageType>*>> m_list;


};