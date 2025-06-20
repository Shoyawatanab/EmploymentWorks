#pragma once
#include "GameBase/Actor.h"

class Canvas;

class DamageCountFactory : public Actor
{
public:
	//コンストラクタ
	DamageCountFactory(Canvas* canvas);
	//デストラクタ
	~DamageCountFactory();
};
