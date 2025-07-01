#include "pch.h"
#include "SelectSceneBackGraund.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
SelectSceneBackGraund::SelectSceneBackGraund(Canvas* canvas)
	:
	Image(canvas, "BackGraund")
{

	//auto image = GetScene()->AddActor<Image>(canvas,"BackGraund");
	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITION);

}

SelectSceneBackGraund::~SelectSceneBackGraund()
{
}
