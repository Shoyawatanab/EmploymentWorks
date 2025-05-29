#include "pch.h"
#include "PlayerLeftArm.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/GameResources.h"

#include "Libraries/WataLib/Animation.h"
#include "Game/CollisiionManager.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="parent">�e</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
PlayerLeftArm::PlayerLeftArm(CommonResources* resources, 
	CharacterEntity* parent
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
:
	PlayerPartsBase(resources, parent, PARTSNAME, scale, position, rotation)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerLeftArm::~PlayerLeftArm()
{
}

/// <summary>
/// ������
/// </summary>
void PlayerLeftArm::Initialize()
{


	//// ���f����ǂݍ���
	auto model = PlayerPartsBase::GetCommonResources()->GetGameResources()->GetModel("PlayerArm");

	PlayerPartsBase::SetModel(model);

	PlayerPartsBase::Initialize();




}

