/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IState.h"
#include "Game/Interface/IObserver.h"

class Player;

class PlayerAttack : public IState , IObserver<GameMessageType>
{
public:

	enum class ThrowState
	{
		RIGHT = 0
		,FRONT
		, LEFT

	};

public:
	//�R���X�g���N�^
	PlayerAttack() ;
	//�f�X�g���N�^
	~PlayerAttack() override;

	//������
	void Initialize(CommonResources* resources) override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

	//�ʒm���ɌĂяo�����
	void Notify(const Telegram<GameMessageType>& telegram) override;


	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(Player* player);


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//
	Player* m_player;
	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//��]
	DirectX::SimpleMath::Quaternion m_rotation;
	//�����̏��
	ThrowState m_throwState;

};