/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IState.h"

class Player;
class Boomerang;

class BoomerangIdle : public IState
{
public:



public:
	//�R���X�g���N�^
	BoomerangIdle() ;
	//�f�X�g���N�^
	~BoomerangIdle() override;


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
	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(Player* player, Boomerang* boomerang);

public:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�u�[������
	Boomerang* m_boomerang;

	Player* m_player;

private :

	
};