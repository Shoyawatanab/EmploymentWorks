#pragma once
#include "GameBase/UI/Button.h"

class Canvas;

class StageTwoButton : public Button
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{880, 360, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{1.4f, 1.4f, 0};
	//�g�嗦
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//�R���X�g���N
	StageTwoButton(Canvas* canvas);
	//�f�X�g���N�^
	~StageTwoButton() override;

private:
	//�N���b�N��
	void OnClick();

	//�͈͓��ɂȂ�����
	void InRange();
	//�͈͊O�ɂȂ�����
	void OutOfRange();


};

