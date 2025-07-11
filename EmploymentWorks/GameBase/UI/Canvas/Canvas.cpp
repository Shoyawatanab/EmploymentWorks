/*
	クラス名     : Canvas
	説明         : UIキャンバスの基底クラス
	補足・注意点 :
*/
#include "pch.h"
#include "Canvas.h"

Canvas::Canvas(Scene* scene)
	:
	Actor(scene)
{
}

Canvas::~Canvas()
{
}
