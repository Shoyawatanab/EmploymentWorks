#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Image;


class BoomerangCount : public Actor
{

	//UI全体の大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 10.0f,10.0f,0.0f };
	//UI全体の座標
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 180.0f,650.0f,0.0f };
	//オフセット
	static constexpr DirectX::SimpleMath::Vector3 OFFSET_POSITION = { 120.0f,0.0f,0.0f };
	//ブーメランUI単体の大きさ
	static constexpr DirectX::SimpleMath::Vector3 BOOMERANG_SCALE = { 100.0f,100.0f,100.0f };

	

public:
	//コンストラクタ
	BoomerangCount(Canvas* canvas);
	//デストラクタ
	~BoomerangCount();
};
