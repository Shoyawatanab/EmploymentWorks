/*
	@file	GameCameraManager.h
	@brief	TPS�J�����N���X
*/
#pragma once
#include "Interface/IGameCamera.h"
#include "Libraries/MyLib/Camera/TPS_Camera.h"
#include "Libraries/MyLib/Camera/GameStartCamera.h"
#include "Libraries/MyLib/Camera/GameEndCamera.h"
#include "Libraries/MyLib/Camera/FPS_Camera.h"

class PlayScene;
class Player;
class Enemy;

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
		GameEndCamera* GetGameEndCamera() { return m_endCamera.get(); }
		FPS_Camera* GetFPSCamera() { return m_fpsCamera.get(); }

	private:

		IGameCamera* m_currentState;
		std::unique_ptr<mylib::TPS_Camera> m_tpsCamera;
		std::unique_ptr<mylib::GameStartCamera> m_startCamera;
		std::unique_ptr<mylib::GameEndCamera> m_endCamera;
		std::unique_ptr<mylib::FPS_Camera> m_fpsCamera;

		PlayScene* m_playScene;
		Player* m_player;
		Enemy* m_enemy;

	public:
		// �R���X�g���N�^
		GameCameraManager();

		// �f�X�g���N�^
		~GameCameraManager() = default;

		void Initialize();


		// �X�V����
		void Update(float elapsedTime);

		void ChangeState(IGameCamera* nestState);

		//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
		void RegistrationInformation(PlayScene* playScene, Player* Player, Enemy* enemy);

		//�N���X�̃C���X�^���X
		void Instances();


	};
}
