#pragma once
#include "GameBase/Camera/Camera.h"


class PlaySceneCameraStateMachine;
class Player2;

class PlaySceneCamera : public Camera
{

public:
	//プレイヤのセット
	void SetPlayer(Player2* player) { m_player = player; }
	//プレイヤの取得
	Player2* GetPlayer() const { return m_player; }
	//X軸回転の取得
	float GetRotationX() const { return m_rotationX; }
	//X軸回転のセット
	void SetRotationX(float rotationX) { m_rotationX = rotationX; }
	//Y軸回転の取得
	float GetRotationY() const { return m_rotationY; }
	//Y軸回転のセット
	void SetRotationY(float rotationY) { m_rotationY = rotationY; }



public:

	//コンストラクタ
	PlaySceneCamera(Scene* scene);
	//デストラクタ
	~PlaySceneCamera() override ;

	//カメラの個別更新処理
	void UpdateCamera(const float& deltaTime) override;


private:
	//ステートマシーン
	std::unique_ptr<PlaySceneCameraStateMachine> m_stateMachine;
	//プレイヤ
	Player2* m_player;

	//横回転
	float m_rotationX;
	//縦回転
	float m_rotationY;

};