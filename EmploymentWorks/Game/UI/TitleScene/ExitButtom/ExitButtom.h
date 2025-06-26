#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Button;

class ExitButtom : public Actor
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{1100, 600, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{1.0f, 1.0f, 0};
	//�g�嗦
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//�R���X�g���N
	ExitButtom(Canvas* canvas);
	//�f�X�g���N�^
	~ExitButtom() override;

private:
	//�N���b�N��
	void OnClick();

	//�͈͓��ɂȂ�����
	void InRange();
	//�͈͊O�ɂȂ�����
	void OutOfRange();

private:

	Button* m_exitButton;

};

