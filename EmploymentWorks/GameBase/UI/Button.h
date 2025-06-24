#pragma once
#include "GameBase/Actor.h"


class Canvas;
class ImageComponent;
class ButtonComponent;


class Button : public Actor
{
public:
	//�R���X�g���N
	Button(Canvas* canvas, const std::string& textureName);
	//�f�X�g���N�^
	~Button();

private:

	ImageComponent* m_imageComponent;

	ButtonComponent* m_buttonComponent;
};
