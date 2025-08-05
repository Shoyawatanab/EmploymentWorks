/*
	�N���X��     : LeftArrowButton
	����         : �Z���N�g�V�[���̃X�e�[�WUI�̍����UI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Button.h"

class Canvas;
class Button;

class LeftArrowButton : public Button
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{170.0f, 250.0f, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.2f, 0.2f, 0};
	//��]
	static constexpr float ROTATE {90.0f};
	//�g�嗦
	static constexpr float MAGNIFICATION { 1.2f };

public:
	//�R���X�g���N
	LeftArrowButton(Canvas* canvas);
	//�f�X�g���N�^
	~LeftArrowButton() override;

private:
	//�N���b�N��
	void OnClick();

	//�͈͓��ɂȂ�����
	void InRange();
	//�͈͊O�ɂȂ�����
	void OutOfRange();


};

