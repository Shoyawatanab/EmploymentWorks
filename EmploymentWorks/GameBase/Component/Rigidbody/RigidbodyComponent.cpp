#include "pch.h"
#include "RigidbodyComponent.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "Game/Params.h"


#include "GameBase/Common/Commons.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="actor">���L��</param>
RigidbodyComponent::RigidbodyComponent(Actor* actor)
	:
	Component(actor)
	,
	m_velocity{}
	,m_addforce{}
	,m_isFixed{false}
	,m_deceleration{1.0f}
	,m_isGravity{true}
{

	//�}�l�[�W���[�ɒǉ�
	auto rigidbodyManager = actor->GetScene()->GetRigidbodyManager();
	rigidbodyManager->AddRigidbody(this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RigidbodyComponent::~RigidbodyComponent()
{
	//�폜
	auto rigidbodyManager = GetActor()->GetScene()->GetRigidbodyManager();
	rigidbodyManager->RemoveRigidbody(this);

}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void RigidbodyComponent::Update(const float& deltaTime)
{

	

	using namespace DirectX::SimpleMath;

	//�Œ�Ȃ�
	if (m_isFixed)
	{
		return;
	}

	//�d�͌v�Z
	if(m_isGravity)
	{
		//�d�͉��Z
		AddForce(Vector3(0.0f, Params::GRAVITY * deltaTime,0.0f));
	}

	//���x�̌v�Z
	auto velocity2 =  m_velocity + m_addforce * deltaTime;

	//�I�u�W�F�N�g�̈ړ�
	GetActor()->GetTransform()->Translate(velocity2);

	//����������
	m_velocity = Vector3::Zero;

	//���C�̌�����
	m_addforce.x *= m_deceleration;
	m_addforce.z *= m_deceleration;






}





