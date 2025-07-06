#pragma once
#include "GameBase/Component.h"
#include "GameBase/Actor.h"
#include "Game/Manager/PickUp/PickUpManager.h"

class PickUpManager;

class PickerComponent : public Component
{
public:

	//��������͈͔͈�
	static constexpr float INITIAL_RADIUS = 1.0f;

public:

	//����͈͂̎擾
	float GetPickUpRadius() const { return m_pickUpRadius; }
	//����\���̎擾�@true:����\ false :����s�\
	float GetIsPickUp() const { return m_isPickUp; }
	//����\���̃Z�b�g�@true:����\ false :����s�\
	void SetIsPickUp(bool isPickUp) { m_isPickUp = isPickUp; }
	//����\��Ԃ̎擾�@true: ����\��ԁ@false:����s�\���
	bool GetIsRecoverable() { return m_isRecoverable; }
	//����\��Ԃ̃Z�b�g�@true: ����\��ԁ@false:����s�\���
	void SetIsRecoverable(bool recoverable) { m_isRecoverable = recoverable; }
	//������̎��s�֐��̃Z�b�g
	void SetOnPickUpFunction(std::function<void()> function) { m_onPickUp = function; };
	//����\���̎��s�֐��̃Z�b�g
	void SetRecoverableFunction(std::function<void()> functoin) { m_recoverable = functoin; }
	//����s�\���̎��s�֐��̃Z�b�g
	void SetUnrecoverableFunction(std::function<void()> function) { m_unrecoverable = function; }

	//����^�C�v�̎擾
	PickUpManager::PickUpType GetPickUpType() { return m_type; }

public:
	//�R���X�g���N
	PickerComponent(Actor* owner,PickUpManager::PickUpType type,float pickUpRadius = INITIAL_RADIUS);
	//�f�X�g���N�^
	~PickerComponent() override;

	//����̎��s
	void TryPickUp();

	//�����
	void OnPickUp();
	//����ł���悤�ɂȂ���
	void OnRecoverable();
	//����ł��Ȃ��Ȃ����Ƃ�
	void OnUnrecoverable();

private:

	//����͈�
	float m_pickUpRadius;

	//����\���@true:����\ false :����s�\
	bool m_isPickUp;
	
	//����\��Ԃ� true: ����\��ԁ@false:����s�\���    ������̔���Ŏg�p
	bool m_isRecoverable;
	//������̎��s�֐�
	std::function<void()> m_onPickUp;
	//����\���̎��s�֐�
	std::function<void()> m_recoverable;
	//����s�\���̎��s�֐�
	std::function<void()> m_unrecoverable;

	//�}�l�[�W���[
	PickUpManager* m_manger;
	//�^�C�v
	PickUpManager::PickUpType m_type;

};