/*
	クラス名     : InformationBase
	説明         : セレクトシーンの右の情報のまとめクラス
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Button;

class InformationBase : public Actor
{
public:
	//コンストラク
	InformationBase(Canvas* canvas);
	//デストラクタ
	~InformationBase() override;


};

