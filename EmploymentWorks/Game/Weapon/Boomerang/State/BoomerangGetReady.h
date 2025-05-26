/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IState.h"

class Boomerang;

class BoomerangGetReady : public IState
{
public:



public:
	//�R���X�g���N�^
	BoomerangGetReady(Boomerang* boomerang) ;
	//�f�X�g���N�^
	~BoomerangGetReady() override;

	//������
	void Initialize(CommonResources* resources) ;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

public:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�u�[������
	Boomerang* m_boomerang;



private :
	
};