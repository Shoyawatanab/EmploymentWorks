#include "pch.h"
#include  "PlaySceneCamera.h"
#include "GameBase/Component/Components.h"
#include "Game/Camera/PayScene/PaySceneCameraState/PlaySceneCameraStateMachine.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
PlaySceneCamera::PlaySceneCamera(Scene* scene)
	:
	Camera(scene)
	,m_stateMachine{}
	, m_rotationX{}
	, m_rotationY{}
{


	SetEyePosition(DirectX::SimpleMath::Vector3(0,5,20));

	m_stateMachine = std::make_unique<PlaySceneCameraStateMachine>(this);

}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneCamera::~PlaySceneCamera()
{

}


/// <summary>
/// カメラの個別更新処理
/// </summary>
/// <param name="deltaTime"></param>
void PlaySceneCamera::UpdateCamera(const float& deltaTime)
{

	m_stateMachine->Update(deltaTime);

}


