#pragma once
#include "GameBase/WataLib/Singleton.h"


class InputMessenger : public Singleton<InputMessenger>
{
	friend class Singleton<InputMessenger>;
public:
	//�R���X�g���N
	InputMessenger();
	//�f�X�g���N�^
	~InputMessenger()override;
	//�ʒm�𑗂�
	void Notify(const DirectX::Keyboard::State& keyboardState);

	//�o�^
	void Rigister(const DirectX::Keyboard::Keys& key, std::function<void(const DirectX::Keyboard::Keys& key)> function);


	// �ώ@�҃��X�g���\�[�g����
	void SortObserverList();
	//  �L�[�͈̓��X�g�𐶐�����
	void CreateKeyRangeList();


private:

	// �L�[�{�[�h���X�g
	std::vector<std::pair<DirectX::Keyboard::Keys, std::function<void(const DirectX::Keyboard::Keys& key)>>> m_keybordList;
	// �L�[�͈̓��X�g(�J�n�C���f�b�N�X�ƏI���C���f�b�N�X)
	std::unordered_map<DirectX::Keyboard::Keys, std::vector<std::pair<size_t, size_t>>> m_keysRangeList;


};
