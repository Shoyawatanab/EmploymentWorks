/*
	�N���X��     : InformationBackGraund
	����         : �Z���N�g�V�[���̉E�̏��̔w�i
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;
class Button;

class InformationBackGraund : public Image
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{1000.0f, 360.0f, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.95f, 0.95f, 0};
	//�g�嗦
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//�R���X�g���N
	InformationBackGraund(Canvas* canvas);
	//�f�X�g���N�^
	~InformationBackGraund() override;


};

