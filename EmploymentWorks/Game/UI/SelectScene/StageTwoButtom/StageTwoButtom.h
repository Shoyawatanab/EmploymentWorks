#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Button;

class StageTwoButtom : public Actor
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
	StageTwoButtom(Canvas* canvas);
	//�f�X�g���N�^
	~StageTwoButtom() override;

private:
	//�N���b�N��
	void OnClick();

	//�͈͓��ɂȂ�����
	void InRange();
	//�͈͊O�ɂȂ�����
	void OutOfRange();

private:

	Button* m_button;

};

