#include "pch.h"
#include "BossEnemyLeftArm.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyPelvis.h"
#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyLeftThigh.h"
#include"Game/Enemys/BossEnemy/PlayerParts/BossEnemyRightThigh.h"
#include "Game/Observer/Messenger.h"

#include "Game/Interface/ICollisionObject.h"
#include "Game/Observer/Messenger.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Params.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="root">�{�X�G�̍��̃N���X</param>
/// <param name="parent">�e</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
BossEnemyLeftArm::BossEnemyLeftArm(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_LEFTARM_HP,
		Params::BOSSENEMY_LEFTARM_BOX_COLLIDER_SIZE, Params::BOSSENEMY_LEFTARM_SPHERE_COLLIDER_SIZE)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyLeftArm::~BossEnemyLeftArm()
{
}

/// <summary>
/// ������
/// </summary>
void BossEnemyLeftArm::Initialize()
{

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	//// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// ���f����ǂݍ���
	auto model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyArm.cmo", *fx);

	BossEnemyPartsBase::SetModel(std::move(model));


	BossEnemyPartsBase::Initialize();
}




void BossEnemyLeftArm::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{


	switch (tag)
	{
		case CollisionEntity::CollisionTag::Stage:
		{

			DirectX::SimpleMath::Vector3 pos = Vector3(2.5f, -3, 2);

			pos = Vector3::Transform(pos, BossEnemyPartsBase::GetRoot()->GetRotation());

			EventParams::CreateParticleDatas aaa = { pos  + BossEnemyPartsBase::GetRoot()->GetPosition()};

			

			Messenger::Notify(EventParams::EventType::CreateParticle, &aaa);
		}
			break;
		default:
			break;
	}


	BossEnemyPartsBase::OnCollisionEnter(object, tag);

}


