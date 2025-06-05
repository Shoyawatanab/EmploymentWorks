/*
	@file	PlayScene.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "PlayScene.h"
#include <cassert>


#include "GameBase/Component/Components.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Player/Player2.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/UI/PlayScene/Canvas/PlaySceneScreenSpaceOverlayCanvas.h"



//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayScene::PlayScene(SceneManager::StageID stageID)
	:
	m_camera{}
{
	//Messenger::GetInstance()->Clear();


	
	

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayScene::~PlayScene()
{

	// do nothing.
	//Messenger::GetInstance()->Clear();



}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayScene::Initialize()
{

	using namespace DirectX::SimpleMath;

	//Messenger::GetInstance()->Rigister(GamePlayMessageType::NEXT_SCENE, this);

	//�J�����̍쐬
	m_camera = AddActor<PlaySceneCamera>(this);
	//�X�e�[�W�t�@�N�g���[�쐬
	AddActor<StageFactory>(this);



	//�v���C���쐬	
	auto player =  AddActor<Player2>(this);
	//�{�X�G�̍쐬
	auto bossEnemy = AddActor<BossEnemy>(this);
	
	auto ui = AddActor<PlaySceneScreenSpaceOverlayCanvas>(this);

	//�v���C���̓o�^
	auto camera = static_cast<PlaySceneCamera*>(m_camera);
	camera->SetPlayer(player);

	player->SetPlaySceneCamera(camera);

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayScene::SceneUpdate(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayScene::SceneRender()
{
	

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// do nothing.
}




void PlayScene::Notify(const Telegram<GamePlayMessageType>& telegram)
{

	switch (telegram.messageType)
	{
		case GamePlayMessageType::NEXT_SCENE:
		{
			auto next = static_cast<Scene::SceneID*>(telegram.extraInfo);

			SetNextSceneID(*next);
		}
			break;
		default:
			break;
	}

}
