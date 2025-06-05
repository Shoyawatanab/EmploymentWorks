#include "pch.h"
#include "BossEnemyPartsBase.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"

#include "Libraries/WataLib/Bounding.h"
#include "GameBase/Manager/CollisiionManager.h"
#include "Libraries/WataLib/Animation.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Params.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="root">�{�X�G�̍��̃N���X</param>
/// <param name="parent">�e</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="partsHP">�p�[�c�̂g�o</param>
/// <param name="boxColliderSize">�{�b�N�X�̓����蔻��̑傫��</param>
/// <param name="SphereColliderSize">�X�t�B�A�̓����蔻��̑傫��</param>
BossEnemyPartsBase::BossEnemyPartsBase(CommonResources* resources
	, BossEnemy* root
	, CharacterEntity* parent
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation
	, const std::string& partsName
	, const int partsHP
	, const DirectX::SimpleMath::Vector3& boxColliderSize
	, const float SphereColliderSize)
	:
	CompositeEntity(resources,scale,position,rotation)
{
	BaseEntity::SetParent(parent);
	BaseEntity::SetIsGravity(false);
}




/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyPartsBase::~BossEnemyPartsBase()
{
	
}


