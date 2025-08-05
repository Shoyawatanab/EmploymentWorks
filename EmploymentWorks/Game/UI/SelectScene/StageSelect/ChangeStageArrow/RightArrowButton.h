/*
	�N���X��     : RightArrowButton
	����         : �Z���N�g�V�[���̃X�e�[�WUI�̉E���UI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Button.h"

class Canvas;
class Button;

class RightArrowButton : public Button
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{530.0f, 250.0f, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.2f, 0.2f, 0};
	//��]
	static constexpr float ROTATE{ 270.0f };
	//�g�嗦
	static constexpr float MAGNIFICATION{ 1.2f };

public:
	//�R���X�g���N
	RightArrowButton(Canvas* canvas);
	//�f�X�g���N�^
	~RightArrowButton() override;

private:
	//�N���b�N��
	void OnClick();

	//�͈͓��ɂȂ�����
	void InRange();
	//�͈͊O�ɂȂ�����
	void OutOfRange();


};

