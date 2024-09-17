/*
	@file	GamePlayUI.h
	@brief	TPS�J�����N���X
*/
#pragma once
#include "Interface/IUI.h"
#include <Libraries/MyLib/UserInterface.h>


// �O���錾
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


		// ���ʃ��\�[�X
		CommonResources* m_commonResources;

		int m_windowWidth, m_windowHeight;


		std::vector<std::unique_ptr<UserInterface>> m_enemyHP;
		std::vector<std::unique_ptr<UserInterface>> m_playerHP;
		Enemy* m_enemy;

		Player* m_player;



	public:
		// �R���X�g���N�^
		GamePlayUI();

		// �f�X�g���N�^
		~GamePlayUI() = default;

		//�I�[�o�[���C�h
	public:

		void Initialize(CommonResources* resources) override;


		void Update(const float& elapsedTime) override;

		void Render() override;

		void Enter() override;

		void Exit() override;

		//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
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
