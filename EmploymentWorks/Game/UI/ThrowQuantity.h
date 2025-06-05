#pragma once
#include "Game/Entities/UIBaseEntity.h"
#include "Game/Interface/IObserver.h"

class UserInterface;

class ThrowQuantity : public UIBaseEntity , public IObserver<GamePlayMessageType>
{

private:

	//���
	enum  class State
	{
		ONE,     //�P�Ȃ���
		THREE	 //�R�Ȃ���
	};


	static constexpr DirectX::SimpleMath::Vector2 THROW_QUANTITYUI_POSITION{1100, 670};
	static constexpr DirectX::SimpleMath::Vector2 THROW_QUANTITYUI_SCALE{0.15f, 0.15f};

	static constexpr DirectX::SimpleMath::Vector2 THROW_QUANTITYUI_OFFSET_POSITION{100, 0};

	static constexpr DirectX::SimpleMath::Vector2 THROW_QUANTITYUI_UP_POSITION{0, -20};


public:


public:
	//�R���X�g���N�^
	ThrowQuantity(CommonResources* resources);
	//�f�X�g���N�^
	~ThrowQuantity();

	//������
	void Initialize();
	//�X�V����
	void  Update(const float& elapsedTime);
	//�`��
	void Render();



private:
	//IObserver
	//�ʒm���ɌĂ΂��֐�
	void Notify(const Telegram<GamePlayMessageType>& telegram)  override;


	//��Ԃ̐؂�ւ�
	void ChangeState();

private:
	//���
	State m_state;

	//�u�[�������̓������UI
	std::vector<std::unique_ptr<UserInterface>> m_throwQuantityUI;


};