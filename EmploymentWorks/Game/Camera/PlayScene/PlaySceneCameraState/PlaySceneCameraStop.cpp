/*
	クラス名    :PlaySceneCameraStop
	説明        :停止カメラ　
	補足・注意点:前の状態で止める
*/
#include "pch.h"
#include "PlaySceneCameraStop.h"
#include "Game/Camera/PlayScene/PlaySceneCamera.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="stateMachine">ステートマシーン</param>
/// <param name="camera">カメラ</param>
PlaySceneCameraStop::PlaySceneCameraStop(PlaySceneCameraStateMachine* stateMachine, PlaySceneCamera* camera)
	:
	m_stateMAchine{ stateMachine }
	, m_camera{ camera }
{



}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneCameraStop::~PlaySceneCameraStop()
{



}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void PlaySceneCameraStop::Update(const float& deltaTime)
{

	UNREFERENCED_PARAMETER(deltaTime);

}

/// <summary>
/// 状態に入った時
/// </summary>
void PlaySceneCameraStop::Enter()
{
	using namespace DirectX::SimpleMath;


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void PlaySceneCameraStop::Exit()
{
}
