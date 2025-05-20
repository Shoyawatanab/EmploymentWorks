/*
	@file	TitleCamera.h
	@brief	TPSカメラクラス
*/
#pragma once
#include "Game/Interface/ICamera.h"



namespace WataLib
{
	class TitleCamera :public ICamera
	{
	private:


		// 画角
		const float FOV = DirectX::XMConvertToRadians(45.0f);

		// 近い投影面
		const float NEAR_PLANE = 1.0f;

		// 遠い投影面
		const float FAR_PLANE = 100.0f;

		//ターゲットまでの距離
		static constexpr DirectX::SimpleMath::Vector3 DISTANCE_TO_TARGET{6.0f, 4.0f, 6.0f};

		static constexpr float ROTATION_SPEED = 0.25f;

	public:
		// getter
		const DirectX::SimpleMath::Matrix& GetViewMatrix() override { return m_view; }

		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }

		const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }

		const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

		const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }



	public:
		// コンストラクタ
		TitleCamera();

		// デストラクタ
		~TitleCamera() = default;
		//初期化
		void Initialize(CommonResources* resources) override;
		//更新処理
		void Update(const float& elapsedTime);
		//状態に入った時
		void Enter() override;
		//状態を抜けた時
		void Exit() override;

		//描画
		void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;

	private:
		// ビュー行列を計算する
		void CalculateViewMatrix();

		// プロジェクション行列を計算する
		void CalculateProjectionMatrix();

		// カメラ座標を計算する
		void CalculateEyePosition(const float& elapsedTime);

	private:

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
		//横回転
		DirectX::SimpleMath::Quaternion m_rotationX;


		//カメラの角度
		float m_angle;


	};
}
