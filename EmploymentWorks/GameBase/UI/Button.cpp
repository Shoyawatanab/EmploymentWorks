#include "pch.h"
#include "Button.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/Component/Components.h"

Button::Button(Canvas* canvas, const std::string& textureName)
	:
	Actor(canvas->GetScene())
	,m_imageComponent{}
	,m_buttonComponent{}
{

	//イメージの追加
	m_imageComponent = AddComponent<ImageComponent>(this, textureName);
	m_buttonComponent = AddComponent<ButtonComponent>(this);

}

Button::~Button()
{
}
