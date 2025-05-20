#include "pch.h"
#include "BossEnemyRightArm.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Libraries/WataLib/GameResources.h"
#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Bounding.h"


#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyPelvis.h"
#include "Game/Enemys/BossEnemy/PlayerParts/BossEnemyLeftThigh.h"
#include"Game/Enemys/BossEnemy/PlayerParts/BossEnemyRightThigh.h"
#include "Game/Observer/Messenger.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
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
BossEnemyRightArm::BossEnemyRightArm(CommonResources* resources,BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_RIGHTARM_HP,
		Params::BOSSENEMY_RIGHTARM_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_RIGHTARM_SPHERE_COLLIDER_SIZE * root->GetScale().x)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyRightArm::~BossEnemyRightArm()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BossEnemyRightArm::Initialize()
{

	//// ���f����ǂݍ���
	auto model =BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BossEnemyArm");

	BossEnemyPartsBase::SetModel(model);

	BossEnemyPartsBase::Initialize();
}


/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void BossEnemyRightArm::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	switch (tag)
	{
		case CollisionEntity::CollisionTag::STAGE:
		{

			//�p�[�e�B�N���̐����̃��b�Z�[�W�𑗂�
			Vector3 pos = BaseEntity::GetPosition();
			pos.y = 0;
			Messenger::GetInstance()->Notify(GameMessageType::CREATE_PARTICLE, &pos);
		}
		break;
		default:
			break;
	}


	BossEnemyPartsBase::OnCollisionEnter(object, tag);


}


