/*
	@file	UI.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "UI.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Object/Enemy/Enemy.h"
#include "Game/Object/Player/Player.h"
#include "Game/Scene/PlayScene.h"

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
UI::UI()
	:
	m_windowHeight(0)
	, m_windowWidth(0)
	, m_commonResources{}

{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
UI::~UI()
{
	// do nothing.


}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void UI::Initialize(CommonResources* resources, int width, int height)
{
	using namespace DirectX::SimpleMath;
	assert(resources);

	m_commonResources = resources;
	m_windowWidth = width;
	m_windowHeight = height;

	m_playUI->SetWindowSize(m_windowWidth, m_windowHeight);
	m_playUI->Initialize(m_commonResources);

	m_clearUI->SetWindowSize(m_windowWidth, m_windowHeight);
	m_clearUI->Initialize(m_commonResources);

	m_overUI->SetWindowSize(m_windowWidth, m_windowHeight);
	m_overUI->Initialize(m_commonResources);

	m_cuurentState = m_playUI.get();

	//m_cuurentState = m_overUI.get();
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void UI::Update(float elapsedTime)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);


	m_cuurentState->Update(elapsedTime);
}

void UI::RegistrationInformation(PlayScene* playScene, Player* player, Enemy* enemy)
{

	//�K�v�ȃ|�C���^����n��
	m_playUI->RegistrationInformation(player, enemy);
	m_overUI->RegistrationInformation(playScene);
	m_clearUI->RegistrationInformation(playScene);


}

void UI::Instances()
{

	m_playUI = std::make_unique<GamePlayUI>();
	m_clearUI = std::make_unique<GameClearUI>();
	m_overUI = std::make_unique<GameOverUI>();

}




//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void UI::Render()
{
	using namespace DirectX::SimpleMath;


	m_cuurentState->Render();



}

void UI::ChangeState(IUI* nextState)
{

	m_cuurentState->Exit();
	m_cuurentState = nextState;
	m_cuurentState->Enter();

}






