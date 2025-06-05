#pragma once
#include "GameBase/Camera/Camera.h"


class PlaySceneCameraStateMachine;
class Player2;

class PlaySceneCamera : public Camera
{

public:
	//�v���C���̃Z�b�g
	void SetPlayer(Player2* player) { m_player = player; }
	//�v���C���̎擾
	Player2* GetPlayer() const { return m_player; }
	//X����]�̎擾
	float GetRotationX() const { return m_rotationX; }
	//X����]�̃Z�b�g
	void SetRotationX(float rotationX) { m_rotationX = rotationX; }
	//Y����]�̎擾
	float GetRotationY() const { return m_rotationY; }
	//Y����]�̃Z�b�g
	void SetRotationY(float rotationY) { m_rotationY = rotationY; }



public:

	//�R���X�g���N�^
	PlaySceneCamera(Scene* scene);
	//�f�X�g���N�^
	~PlaySceneCamera() override ;

	//�J�����̌ʍX�V����
	void UpdateCamera(const float& deltaTime) override;


private:
	//�X�e�[�g�}�V�[��
	std::unique_ptr<PlaySceneCameraStateMachine> m_stateMachine;
	//�v���C��
	Player2* m_player;

	//����]
	float m_rotationX;
	//�c��]
	float m_rotationY;

};