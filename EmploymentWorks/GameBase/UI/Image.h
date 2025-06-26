#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Component/UI/ImageComponent.h"

class Canvas;
class ImageComponent;

class Image : public Actor
{
public:

	//�؂���͈͂̃Z�b�g
	void SetCutRange(DirectX::SimpleMath::Vector4 range) { m_imageComponent->SetCutRange(range); }
	//�F�̃Z�b�g
	void SetColor(DirectX::SimpleMath::Vector4 color) { m_imageComponent->SetColor(color); }

	//���̓h��Ԃ��ʁ@�O�`�P�܂ł͈̔�
	void SetHorizontalFillAmount(float fillAmount) { m_imageComponent->SetHorizontalFillAmount(fillAmount); }
	//�J�X�^���`��֐��̓o�^
	void SetCustomRenderFunction(std::function<void()> customRender) { m_imageComponent->SetCustomRenderFunction(customRender); }

public:

	//�R���X�g���N�^
	Image(Canvas* canvas, const std::string& textureName);
	//�f�X�g���N�^
	~Image();

private:

	ImageComponent* m_imageComponent;


};