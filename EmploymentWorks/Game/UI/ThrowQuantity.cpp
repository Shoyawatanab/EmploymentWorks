#include "pch.h"
#include "ThrowQuantity.h"
#include "Libraries/WataLib/UserInterface.h"
#include "Game/Observer/Messenger.h"

/// <summary>
/// 
/// </summary>
ThrowQuantity::ThrowQuantity(CommonResources* resources,
	const DirectX::SimpleMath::Vector2& scale,
	const DirectX::SimpleMath::Vector2& position)
	:
	UIBaseEntity(resources,scale,position)
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

	//基底クラスの初期化
	UIBaseEntity::Initialize();

	auto one = std::make_unique<UserInterface>();

	one->Create(UIBaseEntity::GetCommonResources(), "BoomerangUI",
		THROW_QUANTITYUI_POSITION, THROW_QUANTITYUI_SCALE);

	m_throwQuantityUI.push_back(std::move(one));

	one = std::make_unique<UserInterface>();

	one->Create(UIBaseEntity::GetCommonResources(), "BoomerangUI",
		THROW_QUANTITYUI_POSITION + THROW_QUANTITYUI_OFFSET_POSITION, THROW_QUANTITYUI_SCALE);

	m_throwQuantityUI.push_back(std::move(one));


}

void ThrowQuantity::Update(const float& elapsedTime)
{
	//オブジェクトが無効でUpdateが無効なら
	if (!UIBaseEntity::GetIsEntityActive() || !UIBaseEntity::GetIsUpdateActive())
	{
		return;
	}

	//基底クラスの更新処理
	UIBaseEntity::Update(elapsedTime);



}

void ThrowQuantity::Render()
{

	//オブジェクトが無効でUpdateが無効なら
	if (!UIBaseEntity::GetIsEntityActive() || !UIBaseEntity::GetIsRenderActive())
	{
		return;
	}

	//基底クラスの描画
	UIBaseEntity::Render();

	for (auto& trowQuantityUI : m_throwQuantityUI)
	{
		trowQuantityUI->Render();
	}

}


void ThrowQuantity::Notify(const Telegram<GamePlayMessageType>& telegram)
{



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
			
			break;
		case ThrowQuantity::State::THREE:
			m_state = State::ONE;

			break;
		default:
			break;
	}


	//
	m_throwQuantityUI[0]->SetScale(m_throwQuantityUI[0]->GetInialScale() * 1.2f);
	//
	m_throwQuantityUI[1]->SetScale(m_throwQuantityUI[1]->GetInialScale());

}
