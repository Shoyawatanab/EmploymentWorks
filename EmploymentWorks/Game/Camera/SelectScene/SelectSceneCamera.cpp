/*
	クラス名     : SelectSceneCamera
	説明         : セレクトシーンカメラ
	補足・注意点 :
*/
#include "pch.h"
#include "SelectSceneCamera.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene"></param>
SelectSceneCamera::SelectSceneCamera(Scene* scene)
	:
	Camera(scene)	
{
}

/// <summary>
/// デストラクタ
/// </summary>
SelectSceneCamera::~SelectSceneCamera()
{
}


