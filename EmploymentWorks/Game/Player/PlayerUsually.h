/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "GameBase/Interface/IState.h"
#include "GameBase/Messenger/IObserver.h"

class Player;
class RigidbodyComponent;


class PlayerUsually : public IObserver
{


public:
	//�R���X�g���N�^
	PlayerUsually(Player* player);
	//�f�X�g���N�^
	~PlayerUsually();
	// �X�V����
	void Update(const float& deltatime) ;


	//�ʒm���ɌĂяo�����
	void Notify(MessageType type, void* datas) override;


private:
	//�ړ�
	void Move(const float& deltatime);
	//��]
	void Rotate(const float& deltatime);
private:
	//�v���C��
	Player* m_player;
	//���W�b�g�{�f�B�[
	RigidbodyComponent* m_rigidbody;

	//�ړ���
	DirectX::SimpleMath::Vector3 m_moveDirection;
	//�u�[���������\���Ă��邩 true: �\���Ă���  false:�\���Ă��Ȃ�
	bool m_isGetReady;

};