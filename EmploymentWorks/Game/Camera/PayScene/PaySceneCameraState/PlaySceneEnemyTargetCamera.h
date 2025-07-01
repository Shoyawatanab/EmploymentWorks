/*
�G��|�����Ƃ��̓G���^�[�Q�b�g�ɂ����J����
*/

#pragma once
#include "GameBase/Interface/IState.h"


class PlaySceneCamera;
class PlaySceneCameraStateMachine;


class PlaySceneEnemyTargetCamera : public IState
{
public:

	//�^�[�Q�b�g�����Eye�̋���
	static constexpr DirectX::SimpleMath::Vector3 EYE_DIRECTION = { -3,3,15 };

public:
	//�R���X�g���N�^
	PlaySceneEnemyTargetCamera(PlaySceneCameraStateMachine* stateMachine, PlaySceneCamera* camera);
	//�f�X�g���N�^
	~PlaySceneEnemyTargetCamera() override;

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
