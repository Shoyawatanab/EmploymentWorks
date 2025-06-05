#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Component/UI/ImageComponent.h"

class Canvas;
class ImageComponent;

class Image : public Actor
{
public:

	//
	void SetRenderRatio(const float& ratio) { m_imageComponent->SetRenderRatio(ratio); }
	//
	float GetRenderRatio() const { return m_imageComponent->GetRenderRatio(); }
	//
	void SetRenderRatioOffset(const float& offset) { m_imageComponent->SetRenderRatioOffset(offset); };
	//
	float GetRenderRatioOffset() const { return m_imageComponent->GetRenderRatioOffset(); }
	//�����x�̃Z�b�g
	void SetAlphaValue(const float& value) { m_imageComponent->SetAlphaValue(value); }
	//�����x�̎擾
	float GetAlphaValue() const { return m_imageComponent->GetAlphaValue(); }



public:
	//�R���X�g���N�^
	Image(Canvas* canvas, std::string textureName);
	//�f�X�g���N�^
	~Image();

private:

	ImageComponent* m_imageComponent;


};