#include "pch.h"
#include "Image.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Component/Components.h"


Image::Image(Canvas* canvas, std::string textureName)
	:
	Actor(canvas->GetScene())
{

	//イメージの追加
	m_imageComponent = AddComponent<ImageComponent>(this, textureName);


}

/// <summary>
/// デストラクタ
/// </summary>
Image::~Image()
{
}
