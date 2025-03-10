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

	enum  class State
	{
		SplineCurve      //������
		, ChaseToPlayer   //�Ԃ��Ă���
	};

public:


	static constexpr float TARGET_LENGTH{ 5.0f };

public:
	//�R���X�g���N�^
	BoomerangFrontThrow() ;
	//�f�X�g���N�^
	~BoomerangFrontThrow() override;

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

	float Lerp(float a, float b, float t);
	
	bool ChaseToTarget(const float& elapsedTime);

	
	//��]
	void Rotation(const float& elapsedTime);

	void ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec);



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�u�[������
	Boomerang* m_boomerang;

	Player* m_player;


	TargetMarker* m_targetMarker;

	WataLib::TPS_Camera* m_tpsCamera;

	//�o�ߎ���
	float m_totalTime;
	//���
	State m_state;

	DirectX::SimpleMath::Vector3 m_targetPosistion;

};