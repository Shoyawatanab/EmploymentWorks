#include "pch.h"
#include "TimeSeparator.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas"></param>
TimeSeparator::TimeSeparator(Canvas* canvas)
	:
	Image(canvas,"Ten")
{

	GetTransform()->SetScale(SCALE);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TimeSeparator::~TimeSeparator()
{
}


