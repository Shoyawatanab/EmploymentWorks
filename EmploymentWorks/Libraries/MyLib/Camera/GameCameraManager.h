/*
	@file	GameCameraManager.h
	@brief	TPSカメラクラス
*/
#pragma once
#include "Interface/IGameCamera.h"
#include "Libraries/MyLib/Camera/TPS_Camera.h"
#include "Libraries/MyLib/Camera/GameStartCamera.h"

class Player;


namespace mylib
{
	class GameCameraManager 
	{
	private:


	public:

		const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_currentState->GetViewMatrix(); }

		IGameCamera* GetGameCameraState() { return m_currentState; }

		GameStartCamera* GetGameStartCamera() { return m_startCamera.get(); }
		TPS_Camera* GetTPSCamera() { return m_tpsCamera.get(); }


	private:

		IGameCamera* m_currentState;
		std::unique_ptr<mylib::TPS_Camera> m_tpsCamera;
		std::unique_ptr<mylib::GameStartCamera> m_startCamera;

		Player* m_player;

	public:
		// コンストラクタ
		GameCameraManager(Player* Player);

		// デストラクタ
		~GameCameraManager() = default;

		void Initialize();


		// 更新処理
		void Update(float elapsedTime);

		void ChangeState(IGameCamera* nestState);

	};
}
