/*
	�N���X��     : PlayScene
	����         : �v���C�V�[��
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "PlayScene.h"
#include <cassert>
#include "Game/Component/Components.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Player/Player.h"
#include "Game/Camera/PlayScene/PlaySceneCamera.h"
#include "Game/Camera/PlayScene/PlaySceneCamera.h"
#include "Game/UI/PlayScene/Canvas/PlaySceneScreenSpaceOverlayCanvas.h"
#include "Game/UI/PlayScene/Canvas/PlaySceneWorldSpaceCanvas.h"
#include "Game/Weapon/WeaponManager.h"
#include "Game/Enemies/EnemyManager.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Effect/EffectFactory.h"
#include "Game/Sound/PlayScene/PlaySceneSound.h"
#include "Game/GlobalGameData.h"
#include "Game/Manager/Managers.h"

/// <summary>
/// �R���X�g���N
/// </summary>
PlayScene::PlayScene()
	:
	m_camera{}
	,m_pickUpManager{}
	,m_playTime{}
{
	
	m_pickUpManager = std::make_unique<PickUpManager>();

	//
	FadeManager::GetInstance()->StartFadeOut();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene()
{

	//�v���C���Ԃ̃Z�b�g
	GlobalGameData::GetInstance()->SetClearTime(m_playTime);


}

/// <summary>
/// ������
/// </summary>
void PlayScene::SceneInitialize()
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

	
	auto overlayCanvas = AddActor<PlaySceneScreenSpaceOverlayCanvas>(this,enemyManger->GetTargets());

	auto worldSpaceCanvas = AddActor<PlaySceneWorldSpaceCanvas>(this);

	//�v���C���̓o�^
	auto camera = static_cast<PlaySceneCamera*>(m_camera)->SetTarget(player);

	player->SetPlaySceneCamera(camera);
	player->SetTargetMarker(overlayCanvas->GetTargetMarker());

	AddActor<EffectFactory>(this);

	AddActor<PlaySceneSound>(this);


	//�N���A�^�C���̃��Z�b�g
	GlobalGameData::GetInstance()->ResetClearTime();



}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void PlayScene::SceneUpdate(const float& deltaTime)
{
	
	m_pickUpManager->Update(deltaTime);


	m_playTime += deltaTime;

}






