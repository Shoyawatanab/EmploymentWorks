/*
	@file	GameClearUI.h
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

		// ���ʃ��\�[�X
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
		// �R���X�g���N�^
		GameClearUI();

		// �f�X�g���N�^
		~GameClearUI() = default;

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
