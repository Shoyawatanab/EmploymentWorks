#pragma once
#include "GameBase/UI/Button.h"

class Canvas;

class RetryButton : public Button
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{480, 450, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.5f, 0.5f, 0};
	//�g�嗦
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//�R���X�g���N
	RetryButton(Canvas* canvas);
	//�f�X�g���N�^
	~RetryButton();

private:
	//�N���b�N��
	void OnClick();

	//�͈͓��ɂȂ�����
	void InRange();
	//�͈͊O�ɂȂ�����
	void OutOfRange();


};
