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

class BoomerangRightThrow : public IState
{

private:

	enum  class State
	{
		SPINECURVE      //������
		, CHASE_TO_PLAYER   //�Ԃ��Ă���
		, PASSING_THROUGH //�ʂ蔲��
	};

public:


	static constexpr float TARGET_LENGTH{ 5.0f };

public:
	//�R���X�g���N�^
	BoomerangRightThrow() ;
	//�f�X�g���N�^
	~BoomerangRightThrow() override;

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
	void AddPointer(Boomerang* boomerang,Player* player, TargetMarker* targetMarker, WataLib::TPS_Camera* tpsCamera);

	//�X�v���C���Ȑ��̊�_�̍쐬
	void CreateSplineCurvePositon();

	//�X�v���C���Ȑ�
	void SplineCurve(const float& elapsedTime);
	//�v���C����ǂ�������
	void ChaseToPlayer(const float& elapsedTime);
	//�ʉ�
	void PassingThrough(const float& elapsedTime);
	
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
	//��������
	DirectX::SimpleMath::Vector3 m_moveDirection;

};