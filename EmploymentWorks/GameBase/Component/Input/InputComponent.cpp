#include "pch.h"
#include "InputComponent.h"
#include "GameBase/Messenger/InputMessenger.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="owner">���L��</param>
InputComponent::InputComponent(Actor* owner)
	:
	Component(owner)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
InputComponent::~InputComponent()
{
}

/// <summary>
/// �o�^
/// </summary>
/// <param name="keys">�o�^�L�[�z��</param>
/// <param name="function">�Ăяo���֐�</param>
void InputComponent::Rigister(std::vector<DirectX::Keyboard::Keys> keys
	, std::function<void(const DirectX::Keyboard::Keys& key)> function)
{
	//Messenger�̎擾
	auto messenger = InputMessenger::GetInstance();


	for (auto key : keys)
	{
		messenger->Rigister(key, function);
	}

}
