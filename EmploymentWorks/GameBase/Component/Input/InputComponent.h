#pragma once
#include "GameBase/Component.h"
#include "GameBase/Actor.h"

class InputComponent : public Component
{
public:
	//�R���X�g���N
	InputComponent(Actor* owner);
	//�f�X�g���N�^
	~InputComponent();

	//�o�^
	void Rigister(std::vector<DirectX::Keyboard::Keys> keys
		, std::function<void(const DirectX::Keyboard::Keys& key)> function);

private:

	//�Ăяo���֐�
	std::function<void(const DirectX::Keyboard::Keys& key)> m_function;


};