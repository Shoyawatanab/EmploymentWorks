/*
	�N���X��     : PlaySceneScreenSpaceOverlayCanvas
	����         : �v���C�V�[���̏�ɉ�ʂɈڂ�UI�L�����o�X
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "PlaySceneScreenSpaceOverlayCanvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/UI/PlayScene/PlaySceneUIs.h"
#include "Game/GlobalGameData.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
PlaySceneScreenSpaceOverlayCanvas::PlaySceneScreenSpaceOverlayCanvas(Scene* scene, std::vector<Actor*> targets)
	:
	ScreenSpaceOverlayCanvas(scene)
	,m_targetMarker{}
{

	//�v���C�V�[���ɂ��傤���́@UI

	//PlyerHp�̍쐬
	GetScene()->AddActor<PlayerHp>(this);
	//�^�[�Q�b�g�}�[�J�[
	m_targetMarker = GetScene()->AddActor<TargetMarker>(this,targets);
	//�u�[�������̃J�E���g
	GetScene()->AddActor<BoomerangCount>(this);
	//�_���[�WUI
	GetScene()->AddActor<DamageCountFactory>(this);
	//�v���C���̃_���[�W�G�t�F�N�g
	GetScene()->AddActor<PlayerDamageEffect>(this);
	//�Q�[���I�[�o�[UI
	GetScene()->AddActor<GameOverUI>(this);
	//���UI
	m_pickUpUI =  GetScene()->AddActor<PickUpUI>(this);


	//�X�e�[�W���Ƃ�UI
	StageUI();


	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::PLAYER_PICKUP_POSSIBLE
			,SceneMessageType::PLAYER_PICKUP_IMPOSSIBLE
		}, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneScreenSpaceOverlayCanvas::~PlaySceneScreenSpaceOverlayCanvas()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void PlaySceneScreenSpaceOverlayCanvas::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::PLAYER_PICKUP_POSSIBLE:
			m_pickUpUI->SetActive(true);
			break;
		case SceneMessageType::PLAYER_PICKUP_IMPOSSIBLE:
			m_pickUpUI->SetActive(false);
			break;
		default:
			break;
	}

}

/// <summary>
/// �X�e�[�W���Ƃ�UI
/// </summary>
void PlaySceneScreenSpaceOverlayCanvas::StageUI()
{
	//�X�e�[�W�ԍ��̎擾
	int StageNumber = GlobalGameData::GetInstance()->GetSelectStateNumber();

	switch (StageNumber)
	{
		case 1:
			break;
		case 2:
			GetScene()->AddActor<BossHp>(this);

			break;
		default:
			break;
	}


}



