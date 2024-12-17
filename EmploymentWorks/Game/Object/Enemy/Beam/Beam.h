/*
	@file	Beam.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Interface/IBeamState.h"
#include "Game/Object/Enemy/Beam/BeamState/BeamIdling.h"
#include "Game/Object/Enemy/Beam/BeamState/BeamAttack.h"
#include "Game/Object/Enemy/Beam/BeamState/BeamAttackEnd.h"
#include "Game/Object/Enemy/Beam/BeamState/BeamPreliminaryAction.h"
#include "Game/DetectionCollision/CollisionManager.h"


// �O���錾
class CommonResources;
class BeamEnergyBall;
class BeamChargeEffect;
class BeamRays;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Beam final
{
public:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
	};


	struct  ChargyBallParamater
	{
		//�����l�@�ŏ��l
		DirectX::SimpleMath::Vector3 InitialScale;
		//�ő�l
		DirectX::SimpleMath::Vector3 MaxScale;
		//�\������̎��ԁ@�i���ߎn�߂Ă���ł܂ł̎��ԁj
		float MaxPreliminaryActionTime;
		//���߂̍ő� (�G�l���M�[�e�̃`���[�W����)
		float AccumulationTime;
		//���߃G�t�F�N�g�̐����Ԋu
		float ChargeEffectCreateTime;
		//�k�����ԁ@Rays�Ɠ���
		float ShrinkTime;
		//�ړ����x
		float MoveSpeed;
	};

	struct  RaysParameter
	{
		//
		DirectX::SimpleMath::Vector3 InitialScale;
		// 
		DirectX::SimpleMath::Vector3 MaxScale;
		//
		float MoveSpeed;
		//�k�����ԁ@ChargyBall�Ɠ���
		float ShrinkTime;
		//


	};

	enum  CurrentClassState
	{
		Idling,
		PreliminaryAction,
		Attack,
		AttackEnd
	};


public:

	 DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

	void SetPosition(DirectX::SimpleMath::Vector3 position) { m_position = position; }

	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }
 
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }

	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }

	void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_rotate = rotate; }

	DirectX::SimpleMath::Vector3 GetScale() { return m_scale; }

	void SetScale(DirectX::SimpleMath::Vector3 scale) { m_scale = scale; }

	DirectX::SimpleMath::Vector3 GetInitialScale() { return m_initialScale; }
	
	IBeamState* GetCurrentState() { return m_currentState; }

	Beamldling* GetBeamIdling() { return m_idling.get(); }

	BeamAttack* GetBeamAttack() { return m_attack.get(); }

	BeamAttackEnd* GetBeamAttackEnd() { return m_attackEnd.get(); }

	BeamPreliminaryAction* GetBeamPreliminaryAction() { return m_preliminaryAction.get(); }

	ChargyBallParamater* GetBeamParamater() { return m_chargyBallParamater.get(); }

	BeamEnergyBall* GetBeamEnergyBall() { return m_energyBall.get(); }

	std::vector<std::unique_ptr< BeamChargeEffect>>&  GetBeamChargeEffect() { return m_chargeEffect; }

	bool GetIsHit() { return m_isHit; }

	BeamRays* GetBeamRays() { return m_rays.get(); }

	RaysParameter* GerBeamRaysParameter() { return m_raysParameter.get(); }

	CurrentClassState GetCurrentClassState() { return m_classState; }

	void SetClassState(CurrentClassState state) { m_classState = state; }

	

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//	���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	
	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector3 m_scale;

	DirectX::SimpleMath::Quaternion m_rotate;
	
	DirectX::SimpleMath::Vector3 m_target;

	DirectX::SimpleMath::Vector3 m_initialScale;

	//State
	IBeamState* m_currentState;

	std::unique_ptr<Beamldling> m_idling;

	std::unique_ptr<BeamAttack> m_attack;

	std::unique_ptr<BeamAttackEnd> m_attackEnd;

	//�\������N���X
	std::unique_ptr<BeamPreliminaryAction> m_preliminaryAction;

	//�r�[���ׂ̍�
	float m_thickness;

	bool m_isHit;

	float m_maxLength;

	std::unique_ptr<BeamEnergyBall> m_energyBall;

	float m_preliminaryActitonTime;

	std::unique_ptr<ChargyBallParamater> m_chargyBallParamater;

	std::vector<std::unique_ptr<BeamChargeEffect>> m_chargeEffect;

	std::vector<BeamChargeEffect*> m_deleteChargeEffect;
	//����
	std::unique_ptr<BeamRays> m_rays;

	std::unique_ptr<RaysParameter> m_raysParameter;

	CurrentClassState m_classState;


public:
	Beam();
	~Beam();

	void Initialize() ;
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) ;
	void Finalize();


	//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
	void RegistrationInformation(CommonResources* resources);

	//�N���X�̃C���X�^���X
	void Instances();

	void RegistrationCollionManager(CollisionManager* collsionManager) ;


public :

	void ChangeState(IBeamState* nextState);

	void CreateParticle();

	void RegistrationDeleteParticle(BeamChargeEffect* effect);

	void DeleteParticle();

};
