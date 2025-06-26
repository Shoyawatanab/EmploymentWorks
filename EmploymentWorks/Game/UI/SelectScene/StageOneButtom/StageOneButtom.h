#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Button;

class StageOneButtom : public Actor
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
	StageOneButtom(Canvas* canvas);
	//�f�X�g���N�^
	~StageOneButtom() override;

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

