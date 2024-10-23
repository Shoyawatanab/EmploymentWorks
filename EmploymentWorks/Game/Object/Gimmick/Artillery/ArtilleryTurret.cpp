/*
	@file	ArtilleryTurret.cpp
	@brief	
*/
#include "pch.h"
#include "ArtilleryTurret.h"
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
#include "Game/Object/Gimmick//Artillery/ArtilleryBullet.h"

const float SCALE(8.6f);

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
ArtilleryTurret::ArtilleryTurret()
	:
	m_commonResources{}
	,m_scale{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
ArtilleryTurret::~ArtilleryTurret()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void ArtilleryTurret::Initialize(CommonResources* resources, PlayScene* playScene, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale, DirectX::SimpleMath::Quaternion Rotate)
{
	using namespace DirectX::SimpleMath;
	assert(resources);
	m_commonResources = resources;
	m_position = position;
	m_scale = Scale;
	m_rotate = Rotate;


	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/ArtilleryTurret.cmo", *fx);

	m_bounding = std::make_unique<Bounding>();

	//�e�̐���
	for (int i = 0; i < 1; i++)
	{
		auto bullet = std::make_unique<ArtilleryBullet>();
		bullet->Initialize(m_commonResources,playScene ,m_position, m_scale,m_rotate);
		m_bullet.push_back(std::move(bullet));
	}

	//����̒e�𑕓U��Ԃɂ���
	m_bullet.begin()->get()->SetBulletState(ArtilleryBullet::BulletState::Loading);


}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void ArtilleryTurret::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	for (auto& bullet : m_bullet)
	{
		if (bullet->GetBulletState() == ArtilleryBullet::BulletState::Flying)
		{
			bullet->Update(elapsedTime);
		}


	}


}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void ArtilleryTurret::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
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



	//�e�̕`��
	for (auto& bullet : m_bullet)
	{
		if (bullet->GetBulletState() != ArtilleryBullet::BulletState::Stock)
		{
			bullet->Render(view, projection);

		}
	}


}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void ArtilleryTurret::Finalize()
{
	// do nothing.
}


void ArtilleryTurret::RegistrationCollionManager(CollisionManager* collsionManager)
{
	//collsionManager->AddCollsion(this);
	
	for (auto& bullet : m_bullet)
	{
		bullet->RegistrationCollionManager(collsionManager);
	}
}



void ArtilleryTurret::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);
}

void ArtilleryTurret::Shot()
{

	m_bullet.begin()->get()->SetBulletState(ArtilleryBullet::BulletState::Flying);


}

