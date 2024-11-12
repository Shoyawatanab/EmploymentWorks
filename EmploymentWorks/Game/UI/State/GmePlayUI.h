/*
	@file	GamePlayUI.h
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



	class GamePlayUI : public IUI
	{
	private:



	public:
		void SetWindowSize(int width,int height)
		{
			m_windowWidth = width;
			m_windowHeight = height;
		}


	private:


		// 共通リソース
		CommonResources* m_commonResources;

		int m_windowWidth, m_windowHeight;


		std::vector<std::unique_ptr<UserInterface>> m_enemyHP;
		std::vector<std::unique_ptr<UserInterface>> m_playerHP;

		std::vector<std::unique_ptr<UserInterface>> m_boomerangUI;

		std::vector<std::unique_ptr<UserInterface>> m_boomerangBackUI;

		Enemy* m_enemy;

		Player* m_player;

		PlayScene* m_playScene;

		//スロー演出時のターゲットマーカー
		std::unique_ptr<UserInterface> m_boomerangMarkerUI;
		DirectX::SimpleMath::Vector2 m_boomerangMakerUIScale;

	public:
		// コンストラクタ
		GamePlayUI();

		// デストラクタ
		~GamePlayUI() = default;

		//オーバーライド
	public:

		void Initialize(CommonResources* resources) override;


		void Update(const float& elapsedTime) override;

		void Render() override;

		void Enter() override;

		void Exit() override;

		//クラスに必要な情報（ポインタ）を登録する
		void RegistrationInformation( Player* player, Enemy* enemy, PlayScene* playScene);

		void BoomerangMakerUpdate();

		void BoomerangMakerRender();

	private:

		//画像の読み込み
		std::unique_ptr<UserInterface> Add(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			, DirectX::SimpleMath::Vector2 scale
			, ANCHOR anchor
			, UserInterface::Kinds kind);


		void CreateEnemyHP();

		void CreatePlayerHP();

		void CreateBoomerang();

		void CreateBoomerangMaker();
	};
