#pragma once
#include"GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"

class PlayerStateMachine;
class PlaySceneCamera;
class RigidbodyComponent;
class PlayerModel;
class AnimatorComponent;
class PlayerUsually;
class TargetMarker;

class Player : public Actor
{
public:

	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::PLAYER; }

	//���f���̎擾
	PlayerModel* GetPlayerModel() { return m_model; }
	//���n���Ă��邩�@true�@���n���Ă�@false�@���ĂȂ�
	bool GetIsGround() const { return m_isGround; }

	//�v���C�V�[���J�����̎擾
	PlaySceneCamera* GetPlaySceneCamera() { return m_playSceneCamera; }
	//�v���C�V�[���J�����̃Z�b�g
	void SetPlaySceneCamera(PlaySceneCamera* camera) { m_playSceneCamera = camera; }

	TargetMarker* GetTargetMarker() { return m_targetMarker; }

	void SetTargetMarker(TargetMarker* targetMarker) { m_targetMarker = targetMarker; }



public:
	//�R���X�g���N�^
	Player(Scene* scene);
	//�f�X�g���N�^
	~Player() override ;
	//�I�u�W�F�N�g�ʂ̍X�V����
	void UpdateActor(const float& deltaTime) override;

	//�����������ɌĂяo�����
	void OnCollisionEnter(ColliderComponent* collider) override;

	//�����葱���Ă���Ƃ��̌Ăяo�����
	void OnCollisionStay(ColliderComponent* collider) override;

	//�Փ˂��I�������Ƃ��ɌĂяo�����
	void OnCollisionExit(ColliderComponent* collider) override;



private:
	//���n�����Ƃ�
	void Landing();
	//�_���[�W��H������Ƃ�
	void AddDamage();

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
	//��ɍs�������N���X
	std::unique_ptr<PlayerUsually> m_usually;
	//���n���Ă��邩
	bool m_isGround;
	//1�t���O�̍��W
	DirectX::SimpleMath::Vector3 m_lastPosition;

	//�^�[�Q�b�g�}�[�J�[
	TargetMarker* m_targetMarker;

	//HP
	int m_hp;

};