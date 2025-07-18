/*
	クラス名     : ResultCamera
	説明         : リザルトシーンカメラ
	補足・注意点 :
*/
#include "pch.h"
#include "ResultCamera.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene"></param>
ResultCamera::ResultCamera(Scene* scene)
	:
	Camera(scene)	
{
	

	SetTargetPosition(DirectX::SimpleMath::Vector3(0,1,0));
	SetEyePosition(DirectX::SimpleMath::Vector3(0, 1, 4));

}

/// <summary>
/// デストラクタ
/// </summary>
ResultCamera::~ResultCamera()
{
}


