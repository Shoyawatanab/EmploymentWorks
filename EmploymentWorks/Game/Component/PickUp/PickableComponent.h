//�E���鑤
#pragma once
#include "GameBase/Component.h"
#include "GameBase/Actor.h"
#include "Game/Manager/PickUp/PickUpManager.h"

class PickableComponent : public Component
{
public:

	//����\���̎擾�@ture:�\  false:�s�\ 
	bool GetIsPossible() { return m_isPossible; }
	//����\���̃Z�b�g�@ture:�\  false:�s�\ 
	void SetIsPossible(const bool& isPossible) {  m_isPossible = isPossible; }

	//������̎��s�֐��̃Z�b�g
	void SetOnPickUpFunction(std::function<void()> function) { m_onPickUp = function; };
	//����\���̎��s�֐��̃Z�b�g
	void SetRecoverableFunction(std::function<void()> functoin) { m_recoverable = functoin; }
	//����s�\���̎��s�֐��̃Z�b�g
	void SetUnrecoverableFunction(std::function<void()> function) { m_unrecoverable = function; }


public:
	//�R���X�g���N
	PickableComponent (Actor* owner, PickUpManager::PickUpType type);
	//�f�X�g���N�^
	~PickableComponent () override;


	//�����
	void OnPickUp();
	//����ł���悤�ɂȂ���
	void OnRecoverable();
	//����ł��Ȃ��Ȃ����Ƃ�
	void OnUnrecoverable();


private:

	//����\���@ture:�\  false:�s�\ 
	bool m_isPossible;

	//������̎��s�֐�
	std::function<void()> m_onPickUp;
	//����\���̎��s�֐�
	std::function<void()> m_recoverable;
	//����s�\���̎��s�֐�
	std::function<void()> m_unrecoverable;
};