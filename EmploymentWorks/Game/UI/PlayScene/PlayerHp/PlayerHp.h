#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Image;

class PlayerHp : public Actor
{
public:

	//UI全体の大きさ
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 10.0f,10.0f,0.0f };
	//UI全体の座標
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 180.0f,550.0f,0.0f };
	//オフセット
	static constexpr DirectX::SimpleMath::Vector3 OFFSET_POSITION = { 100.0f,0.0f,0.0f };
	//ハートの大きさ
	static constexpr DirectX::SimpleMath::Vector3 HEART_SCALE = { 70.0f,70.0f,100.4f };

public:
	//コンストラクタ
	PlayerHp(Canvas* canvas);
	//デストラクタ
	~PlayerHp();

private:

	std::vector<Image*> m_heart;

};