#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class SelectSceneBackGraund : public Image
{
public:
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 0.4f,0.4f,0.4f };
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 640,360,0 };

public:
	//�R���X�g���N
	SelectSceneBackGraund(Canvas* canvas);
	//�f�X�g���N�^
	~SelectSceneBackGraund() override;


};