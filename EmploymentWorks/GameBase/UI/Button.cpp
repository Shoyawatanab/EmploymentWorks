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

	//�C���[�W�̒ǉ�
	m_imageComponent = AddComponent<ImageComponent>(canvas,this, textureName);
	m_buttonComponent = AddComponent<ButtonComponent>(this);

}

Button::~Button()
{
}
