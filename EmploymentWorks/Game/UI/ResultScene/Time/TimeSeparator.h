/*
	�N���X��     : TimeSeparator
	����         : ���U���g�V�[���̎���UI�̕��ƕb�̊Ԃ̓_��UI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class TimeSeparator : public Image
{

	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 1.0f,1.0f,1.0f };

public:
	//�R���X�g���N
	TimeSeparator(Canvas* canvas);
	//�f�X�g���N�^
	~TimeSeparator() override;


};
