#include "pch.h"
#include "PlayerLeftFeet.h"
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
PlayerLeftFeet::PlayerLeftFeet(CommonResources* resources 
	, CharacterEntity* parent
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
PlayerLeftFeet::~PlayerLeftFeet()
{
}

/// <summary>
/// ������
/// </summary>
void PlayerLeftFeet::Initialize()
{

	//// ���f����ǂݍ���
	auto model = PlayerPartsBase::GetCommonResources()->GetGameResources()->GetModel("PlayerFeet");

	PlayerPartsBase::SetModel(model);

	PlayerPartsBase::Initialize();


}

