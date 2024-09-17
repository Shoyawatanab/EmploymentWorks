/*
	@file	GameClearUI.h
	@brief	TPSカメラクラス
*/
#pragma once
#include "Interface/IUI.h"
#include <Libraries/MyLib/UserInterface.h>

// 前方宣言
class CommonResources;
class Enemy;
class Player;

class PlayScene;



	class GameClearUI : public IUI
	{
	public:
		enum class NextState
		{
			ReTry,
			Title
		};



	public:
		void SetWindowSize(float width, float height)
		{
			m_windowWidth = width;
			m_windowHeight = height;
		}


		bool GetIsChangeResultScene() { return m_changeResultScene; }

	private:

		// 共通リソース
		CommonResources* m_commonResources;

		int m_windowWidth, m_windowHeight;
		std::unique_ptr<UserInterface> m_clearUI;
		std::unique_ptr<UserInterface> m_reTryUI;
		std::unique_ptr<UserInterface> m_titleUI;


		float m_clearTime;

		bool m_changeResultScene;

		NextState m_nextState;
		PlayScene* m_playScene;

	public:
		// コンストラクタ
		GameClearUI();

		// デストラクタ
		~GameClearUI() = default;

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

		void ClearTexAdd(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			, DirectX::SimpleMath::Vector2 scale
			, ANCHOR anchor
			, UserInterface::Kinds kind);

		void ReTryTexAdd(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			, DirectX::SimpleMath::Vector2 scale
			, ANCHOR anchor
			, UserInterface::Kinds kind);

		void TitleTexAdd(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			, DirectX::SimpleMath::Vector2 scale
			, ANCHOR anchor
			, UserInterface::Kinds kind);




		void CreateClearTex();



	};
