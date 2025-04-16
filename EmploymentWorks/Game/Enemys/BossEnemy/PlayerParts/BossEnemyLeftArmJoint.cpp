#include "pch.h"
#include "BossEnemyLeftArmJoint.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyLeftArm.h"
#include "Game/Observer/Messenger.h"
#include "Game/Weapon/Boomerang/Boomerang.h"

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
BossEnemyLeftArmJoint::BossEnemyLeftArmJoint(CommonResources* resources,BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_LEFTARMJOINT_HP,
		Params::BOSSENEMY_LEFTARMJOINT_BOX_COLLIDER_SIZE, Params::BOSSENEMY_LEFTARMJOINT_SPHERE_COLLIDER_SIZE)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyLeftArmJoint::~BossEnemyLeftArmJoint()
{
}

/// <summary>
/// ������
/// </summary>
void BossEnemyLeftArmJoint::Initialize()
{
	
	auto device = BaseEntity
		::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	//// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// ���f����ǂݍ���
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyArmJoint");

	BossEnemyPartsBase::SetModel(model);

	BossEnemyPartsBase::Initialize();

	//�uLeftArm�v�𐶐�����
	AddChild(std::make_unique<BossEnemyLeftArm>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_LEFTARM_SCALE,
		Params::BOSSENEMY_LEFTARM_POSITION,
		Params::BOSSENEMY_LEFTARM_ROTATION));
}





