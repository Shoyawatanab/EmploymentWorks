/*
	@file	GameStartCamera.h
	@brief	TPSカメラクラス
*/
#pragma once
#include "Interface/IGameCamera.h"

class Player;



namespace mylib
{
	class GameStartCamera :public IGameCamera
	{
	private:



	public:
		// getter
		const DirectX::SimpleMath::Matrix& GetViewMatrix() override { return m_view; }

		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }

		const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }

		const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

		const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }

		DirectX::SimpleMath::Quaternion GetRotationX() { return m_rotationX; }


		void SetCameraEndPos(DirectX::SimpleMath::Vector3 endPos) { m_cameraEndPos = endPos; }

		const float& GetLerpTime() { return m_lerpTime; }

	private:
		// ターゲットからのデフォルト距離
		const float CAMERA_DISTANCE = 7.0f;
		const float CAMERA_HIGHT = 5.0f;

		// 画角
		const float FOV = DirectX::XMConvertToRadians(45.0f);

		// 近い投影面
		const float NEAR_PLANE = 1.0f;

		// 遠い投影面
		const float FAR_PLANE = 100.0f;

		// ビュー行列
		DirectX::SimpleMath::Matrix m_view;

		// プロジェクション行列
		DirectX::SimpleMath::Matrix m_projection;

		// カメラ座標
		DirectX::SimpleMath::Vector3 m_eye;

		// 注視点
		DirectX::SimpleMath::Vector3 m_target;

		// カメラの頭の方向
		DirectX::SimpleMath::Vector3 m_up;

		Player* m_player;

		DirectX::SimpleMath::Quaternion m_rotationX;


		float m_lerpTime;


		//カメラの角度
		float m_angle;
		//カメラの高さ
		float m_height;
		//
		float m_distanceFromTarget;

		DirectX::SimpleMath::Vector3 m_cameraEndPos;
		DirectX::SimpleMath::Vector3 m_endTarget;

	public:
		// コンストラクタ
		GameStartCamera(Player* Player);

		// デストラクタ
		~GameStartCamera() = default;

		// 更新処理

		//オーバーライド
	public:

		void Initialize() override;


		void Update(const float& elapsedTime);

		void Enter() override;

		void Exit() override;


	private:
		// ビュー行列を計算する
		void CalculateViewMatrix();

		// プロジェクション行列を計算する
		void CalculateProjectionMatrix();

		// カメラ座標を計算する
		void CalculateEyePosition();
	};
}
