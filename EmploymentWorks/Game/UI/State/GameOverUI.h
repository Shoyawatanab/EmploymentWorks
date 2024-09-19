/*
	@file	GameOverUI.h
	@brief	TPSカメラクラス
*/
#pragma once
#include "Interface/IUI.h"
#include <Libraries/MyLib/UserInterface.h>


// 前方宣言
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

		// 共通リソース
		CommonResources* m_commonResources;
		int m_windowWidth, m_windowHeight;

		std::unique_ptr<UserInterface> m_gameOverUI;
		std::unique_ptr<UserInterface> m_gameOverReTryUI;
		std::unique_ptr<UserInterface> m_gameOverEndUI;
		PlayScene* m_playScene;

		NextState m_nextState;

	public:
		// コンストラクタ
		GameOverUI();

		// デストラクタ
		~GameOverUI() = default;

		//オーバーライド
	public:

		void Initialize(CommonResources* resources) override;


		void Update(const float& elapsedTime) override;

		void Render() override;

		void Enter() override;

		void Exit() override;

		//クラスに必要な情報（ポインタ）を登録する
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
