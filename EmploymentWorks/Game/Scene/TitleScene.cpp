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

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleScene::TitleScene()
	:
	m_projection{}

{

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
void TitleScene::SceneUpdate(float elapsedTime)
{
	// �錾���������A���ۂ͎g�p���Ă��Ȃ��ϐ�
	UNREFERENCED_PARAMETER(elapsedTime);


	//const auto& state = m_commonResources->GetInputManager()->GetMouseState();

	const auto& tracker = CommonResources::GetInstance()->GetInputManager()->GetMouseTracker();

	//RECT rect{ m_commonResources->GetDeviceResources()->GetOutputSize() };

	////��ʃT�C�Y�̎擾
	//float widht = static_cast<float>(m_commonResources->GetDeviceResources()->GetOutputSize().right);
	//float height = static_cast<float>(m_commonResources->GetDeviceResources()->GetOutputSize().bottom);

	//Vector2 mousePosition = Vector2(state.x * Screen::WIDTH / widht, state.y * Screen::HEIGHT / height) ;
	////Vector2 mousePosition = Vector2(state.x , state.y) ;
	//
	////������
	//m_selectButtomId = BUTTOM_INIAL_ID;
	//
	//for (auto& buttom : m_buttom)
	//{
	//	buttom.second->SetScale(buttom.second->GetInialScale());

	//	if (WataLib::DetectionCollision::Circle_RectCheckHit(Vector2(mousePosition.x,mousePosition.y), Params::MOUSE_RADIUS,
	//		buttom.second->GetPosition(), static_cast<float>(buttom.second->GetWidth()), static_cast<float>(buttom.second->GetHeight())))
	//	{
	//		buttom.second->SetScale(buttom.second->GetInialScale() * 1.4f);

	//		m_selectButtomId = buttom.first;
	//		break;

	//	}
	//}

	//
	//if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	//{
	//	ChangeScene(SceneID::PLAY);

	//	//if (m_selectButtomId != BUTTOM_INIAL_ID)
	//	//{

	//	//	switch (m_selectButtomId)
	//	//	{
	//	//		case 0:
	//	//			m_isChangeScene = true;
	//	//			ChangeScene(SceneID::PLAY);
	//	//			break;
	//	//		case 1:
	//	//			PostQuitMessage(0);
	//	//			break;
	//	//		default:
	//	//			break;
	//	//	}
	//	//}
	//}



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
