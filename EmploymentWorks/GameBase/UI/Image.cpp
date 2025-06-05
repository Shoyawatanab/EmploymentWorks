#include "pch.h"
#include "Image.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Component/Components.h"


Image::Image(Canvas* canvas, std::string textureName)
	:
	Actor(canvas->GetScene())
{

	//�C���[�W�̒ǉ�
	m_imageComponent = AddComponent<ImageComponent>(this, textureName);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Image::~Image()
{
}
