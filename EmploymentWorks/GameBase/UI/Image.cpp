#include "pch.h"
#include "Image.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�L�����o�X</param>
/// <param name="textureName">�摜��</param>
Image::Image(Canvas* canvas, const std::string& textureName)
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
