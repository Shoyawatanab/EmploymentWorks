/*
	@file	ResultScene.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "ResultScene.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

#include "Libraries/WataLib/Fade.h"
#include "Libraries/WataLib/DrawTexture.h"
#include "Game/Score.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
ResultScene::ResultScene()
	:
	m_commonResources{},
	m_isChangeScene{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
ResultScene::~ResultScene()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void ResultScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();




	// �V�[���ύX�t���O������������
	m_isChangeScene = false;


	//�t�F�[�h�A�E�g�̊J�n
	m_commonResources->GetFade()->StartNormalFadeOut();

	m_commonResources->GetScore()->Reset();

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void ResultScene::Update(float elapsedTime)
{
	// �錾���������A���ۂ͎g�p���Ă��Ȃ��ϐ�
	UNREFERENCED_PARAMETER(elapsedTime);

	//�t�F�[�h���I���܂�
	if (m_commonResources->GetFade()->GetFadeState() != Fade::FadeState::None)
	{
		return;
	}

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	m_commonResources->GetScore()->Update(elapsedTime);

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void ResultScene::Render()
{

	m_commonResources->GetScore()->Render();

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void ResultScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID ResultScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		if (m_commonResources->GetFade()->GetFadeState() == Fade::FadeState::None)
		{
			m_commonResources->GetFade()->StartNormalFadeIn();
		}

		return IScene::SceneID::PLAY;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}
