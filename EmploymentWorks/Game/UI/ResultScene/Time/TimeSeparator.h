#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class TimeSeparator : public Image
{

	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 0.1f,0.1f,0.7f };

public:
	//�R���X�g���N
	TimeSeparator(Canvas* canvas);
	//�f�X�g���N�^
	~TimeSeparator() override;


};
