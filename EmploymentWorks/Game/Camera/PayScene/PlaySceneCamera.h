#pragma once
#include "GameBase/Camera/Camera.h"


class PlaySceneCameraStateMachine;
class Player;

class PlaySceneCamera : public Camera
{

public:
	//�v���C���̃Z�b�g
	PlaySceneCamera* SetPlayer(Player* player) { m_player = player; return this; }
	//�v���C���̎擾
	Player* GetPlayer() const { return m_player; }
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
	Player* m_player;

	//����]
	float m_rotationX;
	//�c��]
	float m_rotationY;

};