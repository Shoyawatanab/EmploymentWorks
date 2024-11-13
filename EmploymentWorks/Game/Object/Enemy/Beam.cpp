/*
	@file	Beam.cpp
	@brief	�r�[���N���X
*/
#include "pch.h"
#include "Beam.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Libraries/MyLib/Bounding.h"
#include "Game/DetectionCollision/CollisionManager.h"

#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/BossEnemy.h"
#include "Game/Object/Enemy/BeamModel.h"

static const int MAXMODELS = 50;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Beam::Beam()
	:
	m_commonResources{},
	m_position{},
	m_rotate{},
	m_generationInterval{},
	m_preliminaryActionTime{}
	,m_enemy{}
	,m_player{}
	,m_models{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Beam::~Beam()
{
	// do nothing.

}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Beam::Initialize(CommonResources* resources, Player* player, Enemy* enemy)
{
	using namespace DirectX::SimpleMath;


	assert(resources);
	m_commonResources = resources;
	m_player = player;
	m_enemy = enemy;



	m_position = DirectX::SimpleMath::Vector3(0, 10, 0);

	m_initialRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(90.0f));
	m_rotate = DirectX::SimpleMath::Quaternion::Identity;


	m_models = std::make_unique<BeamModel>();
	m_models->Initialize(m_commonResources, DirectX::SimpleMath::Vector3::Zero, 2.5f);

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Beam::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);




}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Beam::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	//auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//auto states = m_commonResources->GetCommonStates();

	for (auto& bounding : m_bounding)
	{
		bounding->DrawBoundingSphere(view, projection);
	}


	for (auto& Draw : m_drawModels)
	{
		Draw->Render(view, projection);
	}

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Beam::Finalize()
{
	// do nothing.

}


/// <summary>
/// �r�[���̍U��
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns>true:�U�����@false:�U���I��</returns>
bool Beam::Attack(float elapsdTime)
{
	////�\������
	//if (m_preliminaryActionTime < 2)
	//{
	//	//if (m_preliminaryActionTime == 0)
	//	//{
	//	//	m_enemy->RegistrationRungingAnimation("Beam");
	//	//}

	//	m_preliminaryActionTime += elapsdTime;
	//	return true;
	//}

	//�\�����삪�I����Ă���P�񂾂��Ăт���
	if (m_bounding.empty())
	{
		//
		m_startPos = m_enemy->GetBeamStartPosition();
		//�v���C���̍��W���r�[���̏I����
		m_endPos = m_player->GetPosition();

		//�r�[���̋O�������߂�
		DirectX::SimpleMath::Vector3 Orbit = m_endPos - m_startPos;

		//�O���̋��������߂�
		float Lenght = Orbit.Length();

		//��������
		float a = 1;

		//�����������߂�
		float Split = Lenght / a;

		Orbit.Normalize();
		//�����������Ƃɍ��W�����߂�
		for (int i = 0; i < Split; i++)
		{
			//�������W�����߂�

			BoundingParameter bounding;
			bounding.Position  = m_startPos + Orbit * a * static_cast<float>( i);
			bounding.Life = 5;
			
			m_keepBoundingParameter.push_back(bounding);
		}

		//�Ō�̂Ƃ�������������Ȃ��悤�ɂ��邩��


		//�P�ڂ̐���
		//���W�̐擪���g�p
		CreateBounding(m_keepBoundingParameter.front().Position, 3.0f);
		//�擪�̒l��n��
		m_boundingParameter.push_back(m_keepBoundingParameter.front());
		//���W�̍X�V
		m_models->SetPos(m_keepBoundingParameter.front().Position);

		//�`�惂�f���̃R�s�[
		auto Copy = std::make_unique<BeamModel>(*m_models);

		m_drawModels.push_back(std::move(Copy));

		//�擪�̍��W���폜����
		m_keepBoundingParameter.erase(m_keepBoundingParameter.begin());


	}


	//�U��
	//2�ڈȍ~�̐���
	if (m_generationInterval >= 0.3f && !m_keepBoundingParameter.empty())
	{
		//���W�̐擪���g�p
		CreateBounding(m_keepBoundingParameter.front().Position, 3.0f);
		//�擪�̒l��n��
		m_boundingParameter.push_back(m_keepBoundingParameter.front());
		//���W�̍X�V
		m_models->SetPos(m_keepBoundingParameter.front().Position);

		//�`�惂�f���̃R�s�[
		auto Copy = std::make_unique<BeamModel>(*m_models);

		m_drawModels.push_back(std::move(Copy));


		//�擪�̍��W���폜����
		m_keepBoundingParameter.erase(m_keepBoundingParameter.begin());

		m_generationInterval = 0;
	}

	//�������Ԃ����炷
	for (auto& bouding : m_boundingParameter)
	{
		bouding.Life -= elapsdTime;


		if (bouding.Life <= 0)
		{
			//�擪��Bounding�̍폜
			m_bounding.erase(m_bounding.begin());
			//�擪��BoundingParameter�̍폜
			m_boundingParameter.erase(m_boundingParameter.begin());
			//�擪�̍폜
			m_drawModels.erase(m_drawModels.begin());
		}

	}

	if (m_bounding.empty())
	{
		//�\������̎��Ԃ̏�����
		m_preliminaryActionTime = 0;
		//m_enemy->RegistrationRungingAnimation("BeamEnd");
		m_enemy->SetRunnginAnimationName("BeamEnd");
		//�U���I��
		return false;
	}



	m_generationInterval += elapsdTime;
	return true;
}


/// <summary>
/// Bounding�N���X�̍쐬
/// </summary>
/// <param name="Pos"></param>
/// <param name="radius"></param>
void Beam::CreateBounding(DirectX::SimpleMath::Vector3 Pos, float radius)
{

	auto bounding = std::make_unique<Bounding>();
	bounding->CreateBoundingSphere(m_commonResources,Pos, radius);


	m_bounding.push_back(std::move(bounding));


}


