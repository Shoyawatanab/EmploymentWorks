/*
	�N���X��     : StageTwoImage
	����         : �Z���N�g�V�[���̃X�e�[�W�Q�̉摜
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class StageTwoImage : public Image
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{350.0f, 250.0f, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.4f, 0.4f, 0};

public:
	//�R���X�g���N
	StageTwoImage(Canvas* canvas);
	//�f�X�g���N�^
	~StageTwoImage() override;



};

