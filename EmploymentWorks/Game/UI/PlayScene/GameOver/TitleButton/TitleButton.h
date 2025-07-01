#pragma once
#include "GameBase/UI/Button.h"

class Canvas;

class TitleButton : public Button
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{804, 450, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.3f, 0.3f, 0};
	//�g�嗦
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//�R���X�g���N
	TitleButton(Canvas* canvas);
	//�f�X�g���N�^
	~TitleButton();

private:
	//�N���b�N��
	void OnClick();

	//�͈͓��ɂȂ�����
	void InRange();
	//�͈͊O�ɂȂ�����
	void OutOfRange();
};
