/*
	@file	TPS_Camera.h
	@brief	TPSカメラクラス
*/
#pragma once
#include "Interface/IGameCamera.h"

class Player;

namespace mylib
{
	class Mouse;
}

namespace mylib
{
	class TPS_Camera :public IGameCamera
	{
	private:
		struct MouseSensitivity //マウス感度の構造体
		{
			float x;
			float y;
		};

		enum class ZoomState
		{
			None,
			ZoomIn,
			ZoomOut
		};



	public:
		// getter
		const DirectX::SimpleMath::Matrix& GetViewMatrix() override  { return m_view; }

		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }

		const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }

		void SetEyePosition(DirectX::SimpleMath::Vector3 pos) {
			m_eye = pos; 	// カメラ座標を計算する
			// ビュー行列を更新する
			CalculateViewMatrix();
		}

		const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

		const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }

		DirectX::SimpleMath::Quaternion GetRotationX() { return m_rotationX; }

		DirectX::SimpleMath::Vector3 GetCameraForward() { return m_forward; }

		//デバック用
		const POINT GetAngle() { return m_angle; }

	private:
		// ターゲットからのデフォルト距離
		const float CAMERA_DISTANCE = 4.0f;
		const float CAMERA_HIGHT = 0.0f;

		// 画角
		const float FOV = DirectX::XMConvertToRadians(45.0f);
		
		// 近い投影面
		const float NEAR_PLANE = 1.0f;
		
		// 遠い投影面
		const float FAR_PLANE  = 100.0f;

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

		mylib::Mouse* m_mouse;
		//回転角度
		POINT m_angle;
		//マウス感度
		MouseSensitivity m_mouseSensitivity;

		float m_lerpTime;

		//構えた時のカメラの動く距離
		DirectX::SimpleMath::Vector3 m_moveEye;

		ZoomState m_zoomState;

		DirectX::SimpleMath::Vector3 m_forward;


	public:
		// コンストラクタ
		TPS_Camera();

		// デストラクタ
		~TPS_Camera();

		//クラスに必要な情報（ポインタ）を登録する
		void RegistrationInformation(Player* Player);


		//オーバーライド
	public:
		// 初期化する
		void Initialize() override ;


		// 更新処理
		void Update(const float& elapsedTime) override;

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
