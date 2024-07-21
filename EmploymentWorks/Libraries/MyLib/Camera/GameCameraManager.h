/*
	@file	GameCameraManager.h
	@brief	TPS�J�����N���X
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
		// �R���X�g���N�^
		GameCameraManager(Player* Player);

		// �f�X�g���N�^
		~GameCameraManager() = default;

		void Initialize();


		// �X�V����
		void Update(float elapsedTime);

		void ChangeState(IGameCamera* nestState);

	};
}
