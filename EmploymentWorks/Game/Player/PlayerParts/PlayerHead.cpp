#include "pch.h"
#include "PlayerHead.h"
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
PlayerHead::PlayerHead(CommonResources* resources, 
	CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation)
	:
	PlayerPartsBase(resources, parent, PARTSNAME, scale, position, rotation)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerHead::~PlayerHead()
{
}

/// <summary>
/// ������
/// </summary>
void PlayerHead::Initialize()
{



	//// ���f����ǂݍ���
	auto model = PlayerPartsBase::GetCommonResources()->GetGameResources()->GetModel("PlayerHead");

	PlayerPartsBase::SetModel(model);

	PlayerPartsBase::Initialize();

}

