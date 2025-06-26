#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Button;

class StageOneButtom : public Actor
{
public:
	//座標
	static constexpr DirectX::SimpleMath::Vector3 POSITOIN{400, 360, 0};
	//大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE{1.4f, 1.4f, 0};
	//拡大率
	static constexpr float MAGNIFICATION{ 1.4f };

public:
	//コンストラク
	StageOneButtom(Canvas* canvas);
	//デストラクタ
	~StageOneButtom() override;

private:
	//クリック時
	void OnClick();

	//範囲内になった時
	void InRange();
	//範囲外になった時
	void OutOfRange();

private:

	Button* m_button;

};

