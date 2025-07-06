#include "pch.h"
#include "TimeSeparator.h"
#include "Game/Component/Components.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas"></param>
TimeSeparator::TimeSeparator(Canvas* canvas)
	:
	Image(canvas,"Ten")
{

	GetTransform()->SetScale(SCALE);

}

/// <summary>
/// デストラクタ
/// </summary>
TimeSeparator::~TimeSeparator()
{
}


