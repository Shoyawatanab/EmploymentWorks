/*
	�N���X��     : PlaySceneWorldSpaceCanvas
	����         : �v���C�V�[����3D��Ԃ̃L�����o�X
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "PlaySceneWorldSpaceCanvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/UI/PlayScene/PlaySceneUIs.h"
#include "Game/GlobalGameData.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Component/Components.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
PlaySceneWorldSpaceCanvas::PlaySceneWorldSpaceCanvas(Scene* scene)
	:
	WorldSpaceCanvas(scene)
{

	GetScene()->AddActor<BossHp>(this);


	//�X�e�[�W���Ƃ�UI
	StageUI();


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneWorldSpaceCanvas::~PlaySceneWorldSpaceCanvas()
{



}

/// <summary>
/// ���G��HP�̒ǉ�
/// </summary>
/// <param name="enemys"></param>
void PlaySceneWorldSpaceCanvas::AddBirdEnemyHP(std::vector<Actor*> enemys)
{

	for (auto& enemy : enemys)
	{
		GetScene()->AddActor<BirdEnemyHP>(this,enemy);

	}

}



/// <summary>
/// �X�e�[�W���Ƃ�UI
/// </summary>
void PlaySceneWorldSpaceCanvas::StageUI()
{
	//�X�e�[�W�ԍ��̎擾
	int StageNumber = GlobalGameData::GetInstance()->GetSelectStageNumber();

	switch (StageNumber)
	{
		case 1:


			break;
		case 2:
			break;
		default:
			break;
	}

	

}



