/*
	@file	StageSelectScene.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "StageSelectScene.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
StageSelectScene::StageSelectScene(SceneManager* sceneManager)
	:
	m_commonResources{},
	m_spriteBatch{},
	m_spriteFont{},
	m_texture{},
	m_texCenter{},
	m_isChangeScene{}
	,m_sceneManager{sceneManager}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
StageSelectScene::~StageSelectScene()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void StageSelectScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();




	// �V�[���ύX�t���O������������
	m_isChangeScene = false;

	m_sceneManager->SetStageID(SceneManager::StageID::Stage1);

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void StageSelectScene::Update(float elapsedTime)
{
	// �錾���������A���ۂ͎g�p���Ă��Ȃ��ϐ�
	UNREFERENCED_PARAMETER(elapsedTime);

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.A)
	{

		

	}
	else if (kbTracker->released.D)
	{

	}

	// �X�y�[�X�L�[�������ꂽ��
	if (kbTracker->pressed.Space)
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void StageSelectScene::Render()
{
	auto states = m_commonResources->GetCommonStates();

	
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void StageSelectScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID StageSelectScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::PLAY;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}
