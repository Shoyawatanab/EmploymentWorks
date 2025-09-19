/*
	�N���X��     : PlaySceneWorldSpaceCanvas
	����         : �v���C�V�[����3D��Ԃ̃L�����o�X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Canvas/WorldSpaceCanvas.h"
#include "Game/Messenger/Messengers.h"


class PlaySceneWorldSpaceCanvas : public WorldSpaceCanvas
{

public:
	//�R���X�g���N�^
	PlaySceneWorldSpaceCanvas(Scene* scene);
	//�f�X�g���N�^
	~PlaySceneWorldSpaceCanvas() override;

	//���IHP�̍쐬
	void AddBirdEnemyHP(std::vector<Actor*> enemys);

private:

	//�X�e�[�W���Ƃ�UI
	void StageUI();


};
