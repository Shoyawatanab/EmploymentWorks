#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class ResultSceneBackGraund : public Image
{
public:
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 0.65f,0.65f,0.4f };
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 760,360,0 };

public:
	//�R���X�g���N
	ResultSceneBackGraund(Canvas* canvas);
	//�f�X�g���N�^
	~ResultSceneBackGraund() override;


};