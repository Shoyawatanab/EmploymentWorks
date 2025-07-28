/*
	�N���X��     : StageOneImage
	����         : �Z���N�g�V�[���̃X�e�[�W�P�̉摜
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;
class Button;

class StageOneImage : public Image
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{350.0f, 250.0f, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.4f, 0.4f, 0};

public:
	//�R���X�g���N
	StageOneImage(Canvas* canvas);
	//�f�X�g���N�^
	~StageOneImage() override;


};

