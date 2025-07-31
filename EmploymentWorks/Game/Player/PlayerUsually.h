/*
	�N���X��     : PlayerUsually
	����         : �v���C���̏�ɏ����������̂̃N���X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Interface/IState.h"
#include "Game/Messenger/Messengers.h"

class Player;
class RigidbodyComponent;
class CommonResources;

class PlayerUsually 
{


public:
	//�R���X�g���N�^
	PlayerUsually(Player* player);
	//�f�X�g���N�^
	~PlayerUsually();
	// �X�V����
	void Update(const float& deltatime) ;


	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);
	//���͎�
	void OnInput(const DirectX::Keyboard::Keys& key);


private:
	//�ړ�
	void Move(const float& deltatime);
	//��]
	void Rotate(const float& deltatime);
	//�}�E�X�z�C�[���̃`�F�b�N
	void CheckMouseWheel();

private:
	//���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�v���C��
	Player* m_player;
	//���W�b�g�{�f�B�[
	RigidbodyComponent* m_rigidbody;

	//�ړ���
	DirectX::SimpleMath::Vector3 m_moveDirection;
	//�u�[���������\���Ă��邩 true: �\���Ă���  false:�\���Ă��Ȃ�
	bool m_isGetReady;

};