#include "pch.h"
#include "PlayerRightArm.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/Animation.h"
#include "Game/CollisiionManager.h"



using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="parent">�e</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
PlayerRightArm::PlayerRightArm(CommonResources* resources, 
	CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation)
	:
	PlayerPartsBase(resources, parent, PARTSNAME, scale, position, rotation)

{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerRightArm::~PlayerRightArm()
{
}

/// <summary>
/// ������
/// </summary>
void PlayerRightArm::Initialize()
{

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	//// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// ���f����ǂݍ���
	auto model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerArm.cmo", *fx);

	PlayerPartsBase::SetModel(std::move(model));

	PlayerPartsBase::Initialize();



}



