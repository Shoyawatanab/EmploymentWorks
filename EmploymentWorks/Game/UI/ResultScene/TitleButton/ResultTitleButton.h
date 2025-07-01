#pragma once
#include "GameBase/UI/Button.h"

class Canvas;

class ResultTitleButton : public Button
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{910, 500, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.9f, 0.9f, 0};
	//�g�嗦
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//�R���X�g���N
	ResultTitleButton(Canvas* canvas);
	//�f�X�g���N�^
	~ResultTitleButton();

private:
	//�N���b�N��
	void OnClick();

	//�͈͓��ɂȂ�����
	void InRange();
	//�͈͊O�ɂȂ�����
	void OutOfRange();
};
