/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IState.h"

class Boomerang;
class Player;
class TargetMarker;

namespace WataLib
{
	class TPS_Camera;
}

class BoomerangFrontThrow : public IState
{

private:
	//���
	enum  class State
	{
		SPINECURVE      //������
		, CHASE_TO_PLAYER   //�Ԃ��Ă���
	};

public:


	static constexpr float TARGET_LENGTH{ 5.0f };

public:
	//�R���X�g���N�^
	BoomerangFrontThrow(Boomerang* boomerang) ;
	//�f�X�g���N�^
	~BoomerangFrontThrow() override;

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

	//�^�[�Q�b�g��ǂ�������
	bool ChaseToTarget(const float& elapsedTime);

	
	//��]
	void Rotation(const float& elapsedTime);
	//��]���̐؂�ւ�
	void ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec);



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�u�[������
	Boomerang* m_boomerang;
	//�v���C��
	Player* m_player;
	//�^�[�Q�b�g�}�[�J�[
	TargetMarker* m_targetMarker;
	//�J����
	WataLib::TPS_Camera* m_tpsCamera;

	//�o�ߎ���
	float m_totalTime;
	//���
	State m_state;
	//�^�[�Q�b�g���W
	DirectX::SimpleMath::Vector3 m_targetPosistion;

};