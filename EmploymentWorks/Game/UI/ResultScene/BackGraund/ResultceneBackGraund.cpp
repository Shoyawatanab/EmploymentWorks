#include "pch.h"
#include "ResultSceneBackGraund.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
ResultSceneBackGraund::ResultSceneBackGraund(Canvas* canvas)
	:
	Image(canvas, "ClearBackGraund")
{

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITION);

}

ResultSceneBackGraund::~ResultSceneBackGraund()
{
}
