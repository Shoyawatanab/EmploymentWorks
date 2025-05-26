/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IState.h"

class Player;

class PlayerIdle : public IState 
{
public:
	//�R���X�g���N�^
	PlayerIdle(Player* player) ;
	//�f�X�g���N�^
	~PlayerIdle() override;

	//������
	void Initialize(CommonResources* resources);
	// �X�V����
	void Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�v���C��
	Player* m_player;
	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//��]
	DirectX::SimpleMath::Quaternion m_rotation;
	
};