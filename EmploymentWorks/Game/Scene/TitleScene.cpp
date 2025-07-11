/*
	�N���X��     : TitleScene
	����         : �^�C�g���V�[��
	�⑫�E���ӓ_ :
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
#include "Game/Component/Components.h"
#include "Game/Fade/FadeManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
	:
	m_camera{}
{

	//FadeManager::GetInstance()->StartFadeOut();

	FadeManager::GetInstance()->StartFadeOut(FadeManager::FadeOutKinds::BOMERANG_FADE_OUT);

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


