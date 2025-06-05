#pragma once
#include "Game/Interface/IState.h"

class PlaySceneCamera;
class PlaySceneCameraStateMachine;

class PlaySceneCameraTPS : public IState
{
public:
	//�}�E�X���W
	static constexpr DirectX::SimpleMath::Vector2 MOUSE_POSITION{640.0f,320.0f};

	//�}�E�X���x
	static constexpr float MOUSE_SENSITIVITY = 0.0005f;
	//�J�����̌��E�p�x
	static constexpr float ROTATE_LIMIT = 1.5f;

	// �^�[�Q�b�g����̃f�t�H���g����
	const float CAMERA_DISTANCE = 4.0f;

public:

	const DirectX::SimpleMath::Vector3& GetForwardVector() const { return m_forward; }

public:
	//�R���X�g���N�^
	PlaySceneCameraTPS(PlaySceneCameraStateMachine* stateMachine,PlaySceneCamera* camera);
	//�f�X�g���N�^
	~PlaySceneCameraTPS();

	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

private:

	//�}�E�X����
	void MouseOperation();

private:
	//�J����
	PlaySceneCamera* m_camera;
	//�X�e�[�g�}�V�[��
	PlaySceneCameraStateMachine* m_stateMAchine;
	//����]
	float m_rotationX;
	//�c��]
	float m_rotationY;
	//���ʃx�N�g��
	DirectX::SimpleMath::Vector3 m_forward;

};