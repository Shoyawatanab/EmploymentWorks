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


		// ���ʃ��\�[�X
		CommonResources* m_commonResources;

		int m_windowWidth, m_windowHeight;


		std::vector<std::unique_ptr<UserInterface>> m_enemyHP;
		std::vector<std::unique_ptr<UserInterface>> m_playerHP;

		std::vector<std::unique_ptr<UserInterface>> m_boomerangUI;

		std::vector<std::unique_ptr<UserInterface>> m_boomerangBackUI;

		Enemy* m_enemy;

		Player* m_player;

		PlayScene* m_playScene;

		//�X���[���o���̃^�[�Q�b�g�}�[�J�[
		std::unique_ptr<UserInterface> m_boomerangMarkerUI;
		DirectX::SimpleMath::Vector2 m_boomerangMakerUIScale;

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
		void RegistrationInformation( Player* player, Enemy* enemy, PlayScene* playScene);

		void BoomerangMakerUpdate();

		void BoomerangMakerRender();

	private:

		//�摜�̓ǂݍ���
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
