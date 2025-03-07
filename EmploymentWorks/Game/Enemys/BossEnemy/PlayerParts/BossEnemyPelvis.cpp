#include "pch.h"
#include "BossEnemyPelvis.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyTorso.h"
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
BossEnemyPelvis::BossEnemyPelvis(CommonResources* resources
	,BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_PELVIS_HP,
		Params::BOSSENEMY_PELVIS_BOX_COLLIDER_SIZE, Params::BOSSENEMY_PELVIS_SPHERE_COLLIDER_SIZE)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyPelvis::~BossEnemyPelvis()
{
}

/// <summary>
/// ������
/// </summary>
void BossEnemyPelvis::Initialize()
{

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	//// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// ���f����ǂݍ���
	auto model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyPelvis.cmo", *fx);

	BossEnemyPartsBase::SetModel(std::move(model));


	BossEnemyPartsBase::Initialize();

	////�uTorso�v�𐶐�����
	AddChild(std::make_unique<BossEnemyTorso>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_TORSO_SCALE,
		Params::BOSSENEMY_TORSO_POSITION,
		Params::BOSSENEMY_TORSO_ROTATION));

}



