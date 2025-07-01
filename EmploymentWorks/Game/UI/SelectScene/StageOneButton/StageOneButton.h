#pragma once
#include "GameBase/UI/Button.h"

class Canvas;
class Button;

class StageOneButton : public Button
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{400, 360, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{1.4f, 1.4f, 0};
	//�g�嗦
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//�R���X�g���N
	StageOneButton(Canvas* canvas);
	//�f�X�g���N�^
	~StageOneButton() override;

private:
	//�N���b�N��
	void OnClick();

	//�͈͓��ɂȂ�����
	void InRange();
	//�͈͊O�ɂȂ�����
	void OutOfRange();


};

