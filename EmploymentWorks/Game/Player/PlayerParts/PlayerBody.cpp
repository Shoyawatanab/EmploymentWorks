#include "pch.h"
#include "PlayerBody.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/GameResources.h"
#include "Libraries/WataLib/Animation.h"

#include "Game/Player/PlayerParts/PlayerHead.h"
#include "Game/Player/PlayerParts/PlayerLeftArm.h"
#include "Game/Player/PlayerParts/PlayerRightArm.h"
#include "Game/Player/PlayerParts/PlayerLeftFeet.h"
#include "Game/Player/PlayerParts/PlayerRightFeet.h"
#include "Game/CollisiionManager.h"
#include "Game/Params.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="parent">�e</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
PlayerBody::PlayerBody(CommonResources* resources
	,CharacterEntity* parent
	, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position
	,DirectX::SimpleMath::Quaternion rotation)
	:
	PlayerPartsBase(resources, parent ,PARTSNAME,scale,position,rotation)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBody::~PlayerBody()
{
}

/// <summary>
/// ������
/// </summary>
void PlayerBody::Initialize()
{


	//// ���f����ǂݍ��ޏ���
	auto model = PlayerPartsBase::GetCommonResources()->GetGameResources()->GetModel("PlayerBody");

	PlayerPartsBase::SetModel(model);

	PlayerPartsBase::Initialize();

	//�uHead�v�𐶐�����
	AddChild(std::make_unique<PlayerHead>(BaseEntity::GetCommonResources(),
		this, 
		Params::PLAYER_HEAD_SCALE, 
		Params::PLAYER_HEAD_POSITION,
		Params::PLAYER_HEAD_ROTATION));
	//�uLeftArm�v�𐶐�����
	AddChild(std::make_unique<PlayerLeftArm>(BaseEntity::GetCommonResources(),
		this,
		Params::PLAYER_LEFRARM_SCALE,
		Params::PLAYER_LEFRARM_POSITION,
		Params::PLAYER_LEFRARM_ROTATION));

	//�uRightArm�v�𐶐�����
	AddChild(std::make_unique<PlayerRightArm>(BaseEntity::GetCommonResources(),
		this,
		Params::PLAYER_RIGHTARM_SCALE,
		Params::PLAYER_RIGHTARM_POSITION,
		Params::PLAYER_RIGHTARM_ROTATION));

	//�uLeftFeet�v�𐶐�����
	AddChild(std::make_unique<PlayerLeftFeet>(BaseEntity::GetCommonResources(),
		this,
		Params::PLAYER_LEFRFEET_SCALE,
		Params::PLAYER_LEFRFEET_POSITION,
		Params::PLAYER_LEFRFEET_ROTATION));

	//�uRightFeet�v�𐶐�����
	AddChild(std::make_unique<PlayerRightFeet>(BaseEntity::GetCommonResources(),
		this, 
		Params::PLAYER_RIGHTFEET_SCALE, 
		Params::PLAYER_RIGHTFEET_POSITION,
		Params::PLAYER_RIGHTFEET_ROTATION));


}

