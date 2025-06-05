#include "pch.h"
#include "ThrowQuantity.h"
#include "Libraries/WataLib/UserInterface.h"
#include "Game/Observer/Messenger.h"

/// <summary>
/// 
/// </summary>
ThrowQuantity::ThrowQuantity(CommonResources* resources)
	:
	UIBaseEntity(resources)
	,m_state{}
{
}

/// <summary>
/// 
/// </summary>
ThrowQuantity::~ThrowQuantity()
{
}

void ThrowQuantity::Initialize()
{

	//���N���X�̏�����
	UIBaseEntity::Initialize();

	auto one = std::make_unique<UserInterface>();

	one->Create(UIBaseEntity::GetCommonResources(), "BoomerangUI",
		THROW_QUANTITYUI_POSITION, THROW_QUANTITYUI_SCALE);

	m_throwQuantityUI.push_back(std::move(one));

	one = std::make_unique<UserInterface>();

	one->Create(UIBaseEntity::GetCommonResources(), "BoomerangUI",
		THROW_QUANTITYUI_POSITION + THROW_QUANTITYUI_OFFSET_POSITION, THROW_QUANTITYUI_SCALE);

	m_throwQuantityUI.push_back(std::move(one));

	m_state = State::ONE;

	//
	m_throwQuantityUI[0]->SetScale(m_throwQuantityUI[0]->GetInialScale() * 1.2f);
	//
	m_throwQuantityUI[1]->SetScale(m_throwQuantityUI[1]->GetInialScale());



	Messenger::GetInstance()->Rigister(GamePlayMessageType::CHANGE_THROW_COUNT, this);


}

void ThrowQuantity::Update(const float& elapsedTime)
{
	//�I�u�W�F�N�g��������Update�������Ȃ�
	if (!UIBaseEntity::GetIsEntityActive() || !UIBaseEntity::GetIsUpdateActive())
	{
		return;
	}

	//���N���X�̍X�V����
	UIBaseEntity::Update(elapsedTime);



}

void ThrowQuantity::Render()
{

	//�I�u�W�F�N�g��������Update�������Ȃ�
	if (!UIBaseEntity::GetIsEntityActive() || !UIBaseEntity::GetIsRenderActive())
	{
		return;
	}

	//���N���X�̕`��
	UIBaseEntity::Render();

	for (auto& trowQuantityUI : m_throwQuantityUI)
	{
		trowQuantityUI->Render();
	}

}

/// <summary>
/// �Q�[���C�x���g�̒ʒm���󂯎��
/// </summary>
/// <param name="telegram"></param>
void ThrowQuantity::Notify(const Telegram<GamePlayMessageType>& telegram)
{


	switch (telegram.messageType)
	{
		case GamePlayMessageType::CHANGE_THROW_COUNT:
			ChangeState();
			break;
		default:
			break;
	}


}

/// <summary>
/// 
/// </summary>
void ThrowQuantity::ChangeState()
{
	switch (m_state)
	{
		case ThrowQuantity::State::ONE:
			m_state = State::THREE;
			//
			m_throwQuantityUI[0]->SetScale(m_throwQuantityUI[0]->GetInialScale());
			//
			m_throwQuantityUI[1]->SetScale(m_throwQuantityUI[1]->GetInialScale() * 1.2f);

			break;
		case ThrowQuantity::State::THREE:
			m_state = State::ONE;
			//
			m_throwQuantityUI[0]->SetScale(m_throwQuantityUI[0]->GetInialScale() * 1.2f);
			//
			m_throwQuantityUI[1]->SetScale(m_throwQuantityUI[1]->GetInialScale());

			break;
		default:
			break;
	}



}
