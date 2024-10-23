/*
	@file	ArtilleryBullet.cpp
	@brief	
*/
#include "pch.h"
#include "ArtilleryBullet.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/DetectionCollision/CollisionManager.h"
#include "Libraries/MyLib/Bounding.h"
#include "Game/Scene/PlayScene.h"
const float SCALE(8.6f);

const float BULLETSPEED(4.0f);

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
ArtilleryBullet::ArtilleryBullet()
	:
	m_commonResources{}
	,m_scale{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
ArtilleryBullet::~ArtilleryBullet()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void ArtilleryBullet::Initialize(CommonResources* resources, PlayScene* playScene, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale, DirectX::SimpleMath::Quaternion Rotate)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;
	m_playScene = playScene;
	m_position = position;
	m_scale = Scale;
	m_rotate = Rotate;
	m_initialPosition = m_position;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/ArtilleryBullet.cmo", *fx);

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, m_scale * 0.4f);
	m_bounding->CreateBoundingSphere(m_commonResources,m_position, 1.0f);

	//��Ԃ��X�g�b�N�ɂ���
	m_bulletState = BulletState::Stock;


}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void ArtilleryBullet::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	DirectX::SimpleMath::Vector3 velocity;
	//���x�̉��Z
	velocity.y += BULLETSPEED * elapsedTime;
	//��]��K�p������
	velocity = Vector3::Transform(velocity, m_rotate);

	m_position += velocity;

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void ArtilleryBullet::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();




	// ���[���h�s����X�V����
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);

	// ���f����`�悷��
	m_model->Draw(context, *states, world, view, projection);


	m_bounding->DrawBoundingSphere(m_position, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);



}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void ArtilleryBullet::Finalize()
{
	// do nothing.
}


void ArtilleryBullet::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}



void ArtilleryBullet::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);

	switch (PartnerTag)
	{
		case CollsionObjectTag::Stage:
		case CollsionObjectTag::Enemy:
			//�����G�t�F�N�g�𐶐�
			m_playScene->CreateParticle(m_position);
			//������
			m_position = m_initialPosition;
			//��ԕω�
			m_bulletState = Loading;
			break;
		default:
			break;
	}

}

