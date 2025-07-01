/*
�G��|�����Ƃ��̓G���^�[�Q�b�g�ɂ����J����
*/

#pragma once
#include "GameBase/Interface/IState.h"


class PlaySceneCamera;
class PlaySceneCameraStateMachine;


class PlaySceneCameraStop : public IState
{
public:

public:
	//�R���X�g���N�^
	PlaySceneCameraStop(PlaySceneCameraStateMachine* stateMachine, PlaySceneCamera* camera);
	//�f�X�g���N�^
	~PlaySceneCameraStop() override;

	// �X�V����
	void Update(const float& deltaTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	//�J����
	PlaySceneCamera* m_camera;
	//�X�e�[�g�}�V�[��
	PlaySceneCameraStateMachine* m_stateMAchine;


};
