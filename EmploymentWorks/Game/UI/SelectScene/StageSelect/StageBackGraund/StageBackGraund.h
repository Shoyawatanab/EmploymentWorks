/*
	�N���X��     : StageBackGraund
	����         : �Z���N�g�V�[���̃X�e�[�WUI�̔w�i
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;
class Button;

class StageBackGraund : public Image
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{350.0f, 250.0f, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.6f, 0.6f, 0};
	//�g�嗦
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//�R���X�g���N
	StageBackGraund(Canvas* canvas);
	//�f�X�g���N�^
	~StageBackGraund() override;


};

