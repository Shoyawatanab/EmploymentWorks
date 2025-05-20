#include "pch.h"
#include "BossEnemyRightThigh.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"

#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyRightLeg.h"
#include "Game/Observer/Messenger.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Params.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="root">�{�X�G�̍��̃N���X</param>
/// <param name="parent">�e</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
BossEnemyRightThigh::BossEnemyRightThigh(CommonResources* resources,
	BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_RIGHTTHIGH_HP,
		Params::BOSSENEMY_RIGHTTHIGH_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_RIGHTTHIGH_SPHERE_COLLIDER_SIZE * root->GetScale().x)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyRightThigh::~BossEnemyRightThigh()
{
}

/// <summary>
/// ������
/// </summary>
void BossEnemyRightThigh::Initialize()
{

	//// ���f����ǂݍ���
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyThigh");

	BossEnemyPartsBase::SetModel(model);

	BossEnemyPartsBase::Initialize();

	//�uRightLeg�v�𐶐�����
	AddChild(std::make_unique<BossEnemyRightLeg>(BaseEntity::GetCommonResources(),
		BossEnemyPartsBase::GetRoot(),
		this,
		Params::BOSSENEMY_RIGHTLEG_SCALE,
		Params::BOSSENEMY_RIGHTLEG_POSITION,
		Params::BOSSENEMY_RIGHTLEG_ROTATION));

}




