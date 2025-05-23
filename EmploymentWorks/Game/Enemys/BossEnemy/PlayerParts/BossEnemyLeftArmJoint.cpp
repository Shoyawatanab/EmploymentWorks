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
BossEnemyLeftArmJoint::BossEnemyLeftArmJoint(CommonResources* resources,BossEnemy* root, CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,	DirectX::SimpleMath::Quaternion rotation)
	:
	BossEnemyPartsBase(resources, root, parent, scale, position, rotation, PARTSNAME, Params::BOSSENEMY_LEFTARMJOINT_HP,
		Params::BOSSENEMY_LEFTARMJOINT_BOX_COLLIDER_SIZE * root->GetScale(), Params::BOSSENEMY_LEFTARMJOINT_SPHERE_COLLIDER_SIZE * root->GetScale().x)
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


/// <summary>
/// �����������ɌĂ΂��֐�
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void BossEnemyLeftArmJoint::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	BossEnemyPartsBase::OnCollisionEnter(object, tag);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::STAGE:
		{
			//�j�󂳂�Ă��Ȃ�
			if (!BossEnemyPartsBase::GetIsPartDestruction())
			{
				//�p�[�e�B�N���̐����̃��b�Z�[�W�𑗂�
				Vector3	pos = BaseEntity::GetPosition();
				pos.y = 0;
				Messenger::GetInstance()->Notify(GameMessageType::CREATE_PARTICLE, &pos);

			}
			else
			{
				//�j�󂳂�Ă���

				//���ʔj��Ŕ����G�t�F�N�g�̐��������b�Z�[�W�ɑ���
				Vector3 scale = BaseEntity::GetScale() * 3;
				Vector3 position = BaseEntity::GetPosition();
				UnknownDataTwo aa = { static_cast<void*>(&position) ,static_cast<void*>(&scale) };

				Messenger::GetInstance()->Notify(GameMessageType::CREATE_EXPLOSION, &aa);

				//�J������h�炷���b�Z�[�W�𑗂�
				float power = 0.1f;
				Messenger::GetInstance()->Notify(GameMessageType::CAMERA_SHAKE, &power);

			}
		}
		break;
		case CollisionTag::BOOMERANG:
			//�p�[�cHP���O�ȉ��Ȃ�
			if (BossEnemyPartsBase::GetPartsHP() <= 0)
			{
				//���ʔj��Ƃ��Đe�q�֌W���Ȃ���
				BaseEntity::SetParent(nullptr);
				//�d�͂��Ȃ���
				BaseEntity::SetIsGravity(true);
				//�p�[�c�j���L����
				BossEnemyPartsBase::SetIsPartDestruction(true);
				//�q�p�[�c�ɒʒm
				for (auto& part : CompositeEntity::GetParts())
				{
					part->NotifyParts(PartMessageType::PART_DESTRUCTION);
				}
			}

			break;

		default:
			break;
	}



}





