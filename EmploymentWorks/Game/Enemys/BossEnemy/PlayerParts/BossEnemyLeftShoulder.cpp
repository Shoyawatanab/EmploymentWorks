#include "pch.h"
#include "BossEnemyLeftShoulder.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyLeftArmJoint.h"
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
BossEnemyLeftShoulder::BossEnemyLeftShoulder(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_LEFTSHOULDER_HP,
		Params::BOSSENEMY_LEFTSHOULDER_BOX_COLLIDER_SIZE, Params::BOSSENEMY_LEFTSHOULDER_SPHERE_COLLIDER_SIZE)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyLeftShoulder::~BossEnemyLeftShoulder()
{
}


/// <summary>
/// ������
/// </summary>
void BossEnemyLeftShoulder::Initialize()
{
	
	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();

	//// ���f����ǂݍ���
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyShoulder");

	BossEnemyPartsBase::SetModel(model);


	BossEnemyPartsBase::Initialize();
	//�uLeftArmJoint�v�𐶐�����
	AddChild(std::make_unique<BossEnemyLeftArmJoint>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_LEFTARMJOINT_SCALE,
		Params::BOSSENEMY_LEFTARMJOINT_POSITION,
		Params::BOSSENEMY_LEFTARMJOINT_ROTATION));


}





