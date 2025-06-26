#include "pch.h"
#include "PlaySceneCameraStateMachine.h"
#include "Game/Camera/PayScene/PaySceneCameraState/PaySceneCameraStates.h"
#include "Game/Messenger/Scene/SceneMessages.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="camera"></param>
PlaySceneCameraStateMachine::PlaySceneCameraStateMachine(PlaySceneCamera* camera)
{
	//各ステートの追加
	AddState(PaySceneCameraState::TPS, std::make_unique<PlaySceneCameraTPS>(this,camera));
	AddState(PaySceneCameraState::ENEMY_TARGET, std::make_unique<PlaySceneEnemyTargetCamera>(this,camera));

	//初期ステートの設定
	SetStartState(PaySceneCameraState::TPS);

	//メッセンジャーに登録
	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::BOSS_DEFEATED
		}, this
	);

}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneCameraStateMachine::~PlaySceneCameraStateMachine()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void PlaySceneCameraStateMachine::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::BOSS_DEFEATED:
			ChangeState(PaySceneCameraState::ENEMY_TARGET);
			break;
		default:
			break;
	}
}
