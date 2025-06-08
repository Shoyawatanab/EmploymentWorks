#pragma once
#include"GameBase/Actor.h"

class PlayerStateMachine;
class PlaySceneCamera;
class RigidbodyComponent;
class PlayerModel;
class AnimatorComponent;

class Player2 : public Actor
{
public:
	//�v���C�V�[���J�����̎擾
	PlaySceneCamera* GetPlaySceneCamera() { return m_playSceneCamera; }
	//�v���C�V�[���J�����̃Z�b�g
	void SetPlaySceneCamera(PlaySceneCamera* camera) { m_playSceneCamera = camera; }
	//���f���̎擾
	PlayerModel* GetPlayerModel() { return m_model; }


public:
	//�R���X�g���N�^
	Player2(Scene* scene);
	//�f�X�g���N�^
	~Player2() override ;
	//�I�u�W�F�N�g�ʂ̍X�V����
	void UpdateActor(const float& deltaTime) override;

	//�����������ɌĂяo�����
	void OnCollisionEnter(ColliderComponent* collider);

	//�����葱���Ă���Ƃ��̌Ăяo�����
	void OnCollisionStay(ColliderComponent* collider);


private:
	//�X�e�[�g�}�V��
	std::unique_ptr<PlayerStateMachine>  m_stateMachine;
	//�v���C�V�[���J����
	PlaySceneCamera* m_playSceneCamera;
	//�d��
	RigidbodyComponent* m_rigidBody;
	//�v���C�����f��
	PlayerModel* m_model;
	//�A�j���[�V����
	AnimatorComponent* m_animation;

};