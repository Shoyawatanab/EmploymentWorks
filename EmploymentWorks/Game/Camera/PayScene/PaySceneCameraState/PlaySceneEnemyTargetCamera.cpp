#include "pch.h"
#include "PlaySceneEnemyTargetCamera.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "GameBase/Component/Components.h"

PlaySceneEnemyTargetCamera::PlaySceneEnemyTargetCamera(PlaySceneCameraStateMachine* stateMachine, PlaySceneCamera* camera)
	:
	m_stateMAchine{stateMachine}
	,m_camera{camera}
{



}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneEnemyTargetCamera::~PlaySceneEnemyTargetCamera()
{



}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void PlaySceneEnemyTargetCamera::Update(const float& deltaTime)
{



}

/// <summary>
/// 状態に入った時
/// </summary>
void PlaySceneEnemyTargetCamera::Enter()
{
	using namespace DirectX::SimpleMath;

	//ターゲットの変更
	m_camera->SetTargetPosition(m_camera->GetTarget()->GetTransform()->GetWorldPosition());

	Vector3 forward;

	forward = Vector3::Transform(EYE_DIRECTION, m_camera->GetTransform()->GetRotate());

	m_camera->SetEyePosition(m_camera->GetTarget()->GetTransform()->GetWorldPosition() + forward);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void PlaySceneEnemyTargetCamera::Exit()
{
}
