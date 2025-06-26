#pragma once
#include "GameBase/Actor.h"

class Canvas;

class SelectSceneBackGraund : public Actor
{
public:
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 0.4f,0.4f,0.4f };
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 640,360,0 };

public:
	//コンストラク
	SelectSceneBackGraund(Canvas* canvas);
	//デストラクタ
	~SelectSceneBackGraund() override;


};