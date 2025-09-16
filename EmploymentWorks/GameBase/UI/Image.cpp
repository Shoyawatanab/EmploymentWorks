/*
	�N���X��     : Image
	����         : �摜UI�̊��N���X
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "Image.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Component/UI/ImageComponent.h"

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
	m_imageComponent = AddComponent<ImageComponent>(canvas,this, textureName);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Image::~Image()
{
}
