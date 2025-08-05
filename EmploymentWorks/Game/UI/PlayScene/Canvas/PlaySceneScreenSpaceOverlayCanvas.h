/*
	�N���X��     : PlaySceneScreenSpaceOverlayCanvas
	����         : �v���C�V�[���̏�ɉ�ʂɈڂ�UI�L�����o�X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/UI/Canvas/ScreenSpaceOverlayCanvas.h"
#include "Game/Messenger/Messengers.h"

class TargetMarker;
class PickUpUI;

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

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas) ;


private:

	//�X�e�[�W���Ƃ�UI
	void StageUI();

	
private:
	//�^�[�Q�b�g�}�[�J�[UI
	TargetMarker* m_targetMarker;
	//���UI
	PickUpUI* m_pickUpUI;
};
