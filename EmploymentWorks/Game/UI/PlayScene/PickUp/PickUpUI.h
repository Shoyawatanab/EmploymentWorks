/*
	クラス名     : PickUpUI
	説明         : 回収可能UI
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Image.h"

class Canvas;

class PickUpUI : public Image
{
public:
	//コンストラク
	PickUpUI(Canvas* canvas);
	//デストラクタ
	~PickUpUI();


};