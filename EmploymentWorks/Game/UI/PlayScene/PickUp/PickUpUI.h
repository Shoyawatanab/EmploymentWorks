/*
	�N���X��     : PickUpUI
	����         : ����\UI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class PickUpUI : public Image
{
public:

	static constexpr DirectX::SimpleMath::Vector3 POSITION{640, 360, 0};
	static constexpr DirectX::SimpleMath::Vector3 SCALE{0.2f, 0.2f, 0};


public:
	//�R���X�g���N
	PickUpUI(Canvas* canvas);
	//�f�X�g���N�^
	~PickUpUI();


};