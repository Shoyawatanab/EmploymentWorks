#pragma once
#include "Libraries/WataLib/Singleton.h"
#include "GameBase/Messenger/IObserver.h"
#include "SceneMessageType.h"
#include <unordered_map>



class SceneMessenger : public Singleton<SceneMessenger>
{
	friend class Singleton<SceneMessenger>;

public:
	//�R���X�g���N�^
	SceneMessenger();
	//�f�X�g���N�^
	~SceneMessenger() override;
	//���X�g�ɓo�^
	void Rigister(std::vector<SceneMessageType> types,IObserver<SceneMessageType>* observer);
	//�ʒm
	void Notify(SceneMessageType type, void* = nullptr);
	//�N���A
	void Clear();

private:

	std::unordered_map<SceneMessageType, std::vector<IObserver<SceneMessageType>*>> m_list;

};




