/*
	�N���X��     : DecisionButton
	����         : �Z���N�g�V�[���̌���̃{�^��
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Button.h"

class Canvas;
class Button;

class DecisionButton : public Button
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{350.0f, 500.0f, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.3f, 0.3f, 0};
	//�g�嗦
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//�R���X�g���N
	DecisionButton(Canvas* canvas);
	//�f�X�g���N�^
	~DecisionButton() override;

private:
	//�N���b�N��
	void OnClick();

	//�͈͓��ɂȂ�����
	void InRange();
	//�͈͊O�ɂȂ�����
	void OutOfRange();


};

