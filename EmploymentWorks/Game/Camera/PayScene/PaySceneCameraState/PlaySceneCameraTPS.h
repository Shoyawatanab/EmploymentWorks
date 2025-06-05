#pragma once
#include "Game/Interface/IState.h"

class PlaySceneCamera;
class PlaySceneCameraStateMachine;

class PlaySceneCameraTPS : public IState
{
public:
	//マウス座標
	static constexpr DirectX::SimpleMath::Vector2 MOUSE_POSITION{640.0f,320.0f};

	//マウス感度
	static constexpr float MOUSE_SENSITIVITY = 0.0005f;
	//カメラの限界角度
	static constexpr float ROTATE_LIMIT = 1.5f;

	// ターゲットからのデフォルト距離
	const float CAMERA_DISTANCE = 4.0f;

public:

	const DirectX::SimpleMath::Vector3& GetForwardVector() const { return m_forward; }

public:
	//コンストラクタ
	PlaySceneCameraTPS(PlaySceneCameraStateMachine* stateMachine,PlaySceneCamera* camera);
	//デストラクタ
	~PlaySceneCameraTPS();

	// 更新する
	void Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

private:

	//マウス操作
	void MouseOperation();

private:
	//カメラ
	PlaySceneCamera* m_camera;
	//ステートマシーン
	PlaySceneCameraStateMachine* m_stateMAchine;
	//横回転
	float m_rotationX;
	//縦回転
	float m_rotationY;
	//正面ベクトル
	DirectX::SimpleMath::Vector3 m_forward;

};