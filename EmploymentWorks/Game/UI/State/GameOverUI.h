/*
	@file	GameOverUI.h
	@brief	TPS�J�����N���X
*/
#pragma once
#include "Interface/IUI.h"
#include <Libraries/MyLib/UserInterface.h>


// �O���錾
class CommonResources;
class PlayScene;


	class GameOverUI : public IUI
	{
	public:
		enum class NextState
		{
			ReTry,
			End
		};




	public:
		void SetWindowSize(int width, int height)
		{
			m_windowWidth = width;
			m_windowHeight = height;
		}



	private:

		// ���ʃ��\�[�X
		CommonResources* m_commonResources;
		int m_windowWidth, m_windowHeight;

		std::unique_ptr<UserInterface> m_gameOverUI;
		std::unique_ptr<UserInterface> m_gameOverReTryUI;
		std::unique_ptr<UserInterface> m_gameOverEndUI;
		PlayScene* m_playScene;

		NextState m_nextState;

	public:
		// �R���X�g���N�^
		GameOverUI();

		// �f�X�g���N�^
		~GameOverUI() = default;

		//�I�[�o�[���C�h
	public:

		void Initialize(CommonResources* resources) override;


		void Update(const float& elapsedTime) override;

		void Render() override;

		void Enter() override;

		void Exit() override;

		//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
		void RegistrationInformation(PlayScene* playScene);

	private:


		void GameOverTexAdd(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			, DirectX::SimpleMath::Vector2 scale
			, ANCHOR anchor
			, UserInterface::Kinds kind);

		void GameOverReTryTexAdd(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			, DirectX::SimpleMath::Vector2 scale
			, ANCHOR anchor
			, UserInterface::Kinds kind);

		void GameOverEndTexAdd(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			, DirectX::SimpleMath::Vector2 scale
			, ANCHOR anchor
			, UserInterface::Kinds kind);


		void CreateGameOverTex();


	};
