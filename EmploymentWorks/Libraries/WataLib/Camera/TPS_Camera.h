/*
	@file	TPS_Camera.h
	@brief	TPSカメラクラス
*/
#pragma once
#include "Game/Interface/ICamera.h"
#include "Game/Interface/IObserver.h"

// 前方宣言
class CommonResources;
class Player;

namespace WataLib
{
	class Mouse;
}

namespace WataLib
{
	class TPS_Camera :public ICamera ,public IObserver<GameMessageType>
	{
	private:
		//マウス感度の構造体
		struct MouseSensitivity 
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

		//デバック用
		const POINT GetAngle() { return m_angle; }
	public:
		// ターゲットからのデフォルト距離
		const float CAMERA_DISTANCE = 4.0f;
		const float CAMERA_HIGHT = 0.0f;

		// 画角
		const float FOV = DirectX::XMConvertToRadians(45.0f);

		// 近い投影面
		const float NEAR_PLANE = 1.0f;

		// 遠い投影面
		const float FAR_PLANE = 100.0f;

		static constexpr float SHAKETIME = 2.0f;

		

		//Getter Setter
	public:
		// getter
		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }

		const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }

		void SetEyePosition(DirectX::SimpleMath::Vector3 pos)
		{
			m_eye = pos; 	// カメラ座標を計算する
			// ビュー行列を更新する
			CalculateViewMatrix();
		}

		const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

		const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }

		DirectX::SimpleMath::Quaternion GetRotationX() { return m_rotationX; }

		DirectX::SimpleMath::Vector3 GetCameraForward() { return m_forward; }

		//////
		//
		void SetZoomState(ZoomState state) { m_zoomState = state; }
		const DirectX::SimpleMath::Matrix& GetViewMatrix() override { return m_view; }


	public:
		// コンストラクタ
		TPS_Camera();

		// デストラクタ
		~TPS_Camera() override ;

		// 初期化する
		void Initialize(CommonResources* resources) override;
		// 更新処理
		void Update(const float& elapsedTime) override;
		//描画
		void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;

		void Enter() override;

		void Exit() override;


		//クラスに必要な情報（ポインタ）を登録する
		void AddPointer(Player* Player);

		// ビュー行列を計算する
		void CalculateViewMatrix();

		// プロジェクション行列を計算する
		void CalculateProjectionMatrix();

		// カメラ座標を計算する
		void CalculateEyePosition();
		//通知時に呼ばれる関数
		void Notify(const Telegram<GameMessageType>& telegram)  override;
		

	private:
		//揺れ
		void Shake(const float& elapsedTime);

	private:
		//宣言
		Player* m_player;
		std::unique_ptr<WataLib::Mouse> m_mouse;

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


		DirectX::SimpleMath::Quaternion m_rotationX;

		//回転角度
		POINT m_angle;
		//マウス感度
		MouseSensitivity m_mouseSensitivity;

		float m_lerpTime;

		//構えた時のカメラの動く距離
		DirectX::SimpleMath::Vector3 m_moveEye;

		ZoomState m_zoomState;

		DirectX::SimpleMath::Vector3 m_forward;

		//カメラを揺らすかどうか
		bool m_isShake;
		//揺れの時間
		float m_shaleTime;
		//揺れの強さ
		float m_shakePower;
		//揺れの座標
		DirectX::SimpleMath::Vector3 m_shakePosition;



	};
}
