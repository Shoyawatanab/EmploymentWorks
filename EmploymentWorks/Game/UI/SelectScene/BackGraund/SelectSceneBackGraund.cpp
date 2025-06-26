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
	Actor(canvas->GetScene())
{

	auto image = GetScene()->AddActor<Image>(canvas,"BackGraund");
	image->GetTransform()->SetScale(SCALE);
	image->GetTransform()->SetPosition(POSITION);

}

SelectSceneBackGraund::~SelectSceneBackGraund()
{
}
