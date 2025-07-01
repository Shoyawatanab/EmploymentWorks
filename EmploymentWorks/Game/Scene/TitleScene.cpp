/*
	@file	TitleScene.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "TitleScene.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Game/Camera/TitleScene/TitleSceneCamera.h"
#include "Game/UI/TitleScene/Canvas/TitleSceneScreenSpaceOverlayCanvas.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Params.h"
#include "GameBase/Component/Components.h"
#include "Game/Fade/FadeManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
	:
	m_projection{}
{

	FadeManager::GetInstance()->StartFadeOut();



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void TitleScene::Initialize()
{


	//�J�����̍쐬
	m_camera = AddActor<TitleSceneCamera>(this);

	//�X�e�[�W�t�@�N�g���[�쐬
	AddActor<StageFactory>(this);


	//���f���̍쐬
	auto model = AddActor<PlayerModel>(this);
	//���f���̑傫�����v���C���̐ݒ��
	model->GetTransform()->SetScale(Params::PLAYER_SCALE);
	model->GetTransform()->Translate(PLAYER_POSITION);
	model->GetTransform()->SetRotate(Params::PLAYER_ROTATION);

	auto ui = AddActor<TitleSceneScreenSpaceOverlayCanvas>(this);

	//�J�����̃^�[�Q�b�g�̃Z�b�g
	m_camera->SetTargetPosition(model->GetTransform()->GetPosition() );




	//// �V�[���ύX�t���O������������
	//m_isChangeScene = false;

	////�t�F�[�h�A�E�g�̊J�n
	//CommonResources::GetInstance()->GetFade()->StartNormalFadeOut();

	//ShowCursor(true);



}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleScene::SceneUpdate(const float& deltaTime)
{
	// �錾���������A���ۂ͎g�p���Ă��Ȃ��ϐ�
	UNREFERENCED_PARAMETER(deltaTime);






}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleScene::SceneRender()
{




	////// �f�o�b�O����\������
	//auto debugString = m_commonResources->GetDebugString();
	//////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().x);
	//////debugString->AddString("Pos %f" ,m_buttom[0]->GetPosition().y);
	//debugString->AddString("X %d" , m_commonResources->GetDeviceResources()->GetOutputSize().right);
	//debugString->AddString("Y %d" , m_commonResources->GetDeviceResources()->GetOutputSize().bottom);


}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TitleScene::Finalize()
{
	// do nothing.
}



void TitleScene::CreateTextures()
{


}
