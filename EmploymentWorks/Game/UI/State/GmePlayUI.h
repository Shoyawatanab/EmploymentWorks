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


	class GamePlayUI : public IUI
	{
	private:



	public:
		void SetWindowSize(float width,float height)
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
		Enemy* m_enemy;

		Player* m_player;



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
		void RegistrationInformation( Player* player, Enemy* enemy);

	private:

		void EnemyHPAdd(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			, DirectX::SimpleMath::Vector2 scale
			, ANCHOR anchor
			, UserInterface::Kinds kind);


		void PlayerHPAdd(const wchar_t* path
			, DirectX::SimpleMath::Vector2 position
			, DirectX::SimpleMath::Vector2 scale
			, ANCHOR anchor
			, UserInterface::Kinds kind);

		void CreateEnemyHP();

		void CreatePlayerHP();


	};
