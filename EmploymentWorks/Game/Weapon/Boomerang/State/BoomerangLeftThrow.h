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

class BoomerangLeftThrow : public IState
{

private:

	enum  class State
	{
		SPINECURVE      //������
		, CHASE_TO_PLAYER   //�Ԃ��Ă���
	};

public:


	static constexpr float TARGET_LENGTH{ 5.0f };

public:
	//�R���X�g���N�^
	BoomerangLeftThrow(Boomerang* boomerang) ;
	//�f�X�g���N�^
	~BoomerangLeftThrow() override;

	//������
	void Initialize(CommonResources* resources) ;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

	//�X�v���C���Ȑ��̊�_�̍쐬
	void CreateSplineCurvePositon();

	//�X�v���C���Ȑ�
	void SplineCurve(const float& elapsedTime);
	//�v���C����ǂ�������
	void ChaseToPlayer(const float& elapsedTime);

	
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

	//�X�v���C���Ȑ��̍��W
	std::vector<DirectX::SimpleMath::Vector3> m_splineCurvePosition;
	//�Y����
	int m_index;
	//�o�ߎ���
	float m_totalTime;
	//���
	State m_state;
	//��]�̏��
	std::pair<DirectX::SimpleMath::Quaternion, DirectX::SimpleMath::Quaternion> m_rotationDatas;
	//����]
	DirectX::SimpleMath::Quaternion m_horizontalRotation;
	//������]
	DirectX::SimpleMath::Quaternion m_initialRotation;
};