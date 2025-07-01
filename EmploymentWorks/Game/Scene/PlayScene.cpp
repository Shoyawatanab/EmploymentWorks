/*
	@file	PlayScene.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "PlayScene.h"
#include <cassert>
#include "GameBase/Component/Components.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Player/Player.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/UI/PlayScene/Canvas/PlaySceneScreenSpaceOverlayCanvas.h"
#include "Game/Weapon/WeaponManager.h"
#include "Game/Enemies/EnemyManager.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Effect/EffectFactory.h"
#include "Game/Sound/PlayScene/PlaySceneSound.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// �R���X�g���N
/// </summary>
PlayScene::PlayScene()
	:
	m_camera{}
	,m_isChangeScene{}
{
	

	FadeManager::GetInstance()->StartFadeOut();
	
	

}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayScene::~PlayScene()
{

	// do nothing.
	//Messenger::GetInstance()->Clear();



}

/// <summary>
/// ������
/// </summary>
void PlayScene::Initialize()
{

	using namespace DirectX::SimpleMath;

	//�J�����̍쐬
	m_camera = AddActor<PlaySceneCamera>(this);
	//�X�e�[�W�t�@�N�g���[�쐬
	AddActor<StageFactory>(this);

	//�v���C���쐬	
	auto player = AddActor<Player>(this);

	//����t�@�N�g���[�̐���
	AddActor<WeaponManager>(this, player);

	auto enemyManger = AddActor<EnemyManager>(this, player);

	
	auto ui = AddActor<PlaySceneScreenSpaceOverlayCanvas>(this,enemyManger->GetEnemys());


	//�v���C���̓o�^
	auto camera = static_cast<PlaySceneCamera*>(m_camera)->SetTarget(player);

	player->SetPlaySceneCamera(camera);
	player->SetTargetMarker(ui->GetTargetMarker());

	AddActor<EffectFactory>(this);

	AddActor<PlaySceneSound>(this);


	//�N���A�^�C���̃��Z�b�g
	GlobalGameData::GetInstance()->ResetClearTime();

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayScene::SceneUpdate(const float& deltaTime)
{
	
	GlobalGameData::GetInstance()->AddClearTime(deltaTime);


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




