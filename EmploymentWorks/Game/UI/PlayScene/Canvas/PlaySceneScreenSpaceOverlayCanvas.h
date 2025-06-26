/*
�v���C�V�[���̃J�����̏�Ɉڂ�Ui�L�����o�X�N���X
*/
#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"
class TargetMarker;


class PlaySceneScreenSpaceOverlayCanvas : public ScreenSpaceOverlayCanvas
{
public:
	//�^�[�Q�b�g�}�[�J�[�̎擾
	TargetMarker* GetTargetMarker() { return m_targetMarker; }

public:
	//�R���X�g���N�^
	PlaySceneScreenSpaceOverlayCanvas(Scene* scene,std::vector<Actor*> targets);
	//�f�X�g���N�^
	~PlaySceneScreenSpaceOverlayCanvas() override;


	
private:

	TargetMarker* m_targetMarker;

};
