#include "pch.h"
#include "Framework/Resources.h"
#include "DeviceResources.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

// Resources�N���X�̃C���X�^���X���擾����
Resources* const Resources::GetInstance()
{
	if (m_resources == nullptr)
	{
		// Resources�N���X�̃C���X�^���X�𐶐�����
		m_resources.reset(new Resources());
	}
	// Resources�N���X�̃C���X�^���X��Ԃ�
	return m_resources.get();
}

// ���\�[�X�����[�h����
void Resources::LoadResource(CommonResources* resources)
{

	auto device = resources->GetDeviceResources()->GetD3DDevice();

	// ���\�[�X�f�B���N�g����ݒ肷��
	std::unique_ptr<DirectX::EffectFactory> playerFx = std::make_unique<DirectX::EffectFactory>(device);
	playerFx->SetDirectory(L"Resources/Models");
	// �u�v���C���v���f�������[�h����
	m_playerModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Player.cmo", *playerFx);

	// ���\�[�X�f�B���N�g����ݒ肷��
	std::unique_ptr<DirectX::EffectFactory> enemyFx = std::make_unique<DirectX::EffectFactory>(device);
	enemyFx->SetDirectory(L"Resources/Models");
	// �u�G�v���f�������[�h����
	m_enemyModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Enemy.cmo", *enemyFx);

	// ���\�[�X�f�B���N�g����ݒ肷��
	std::unique_ptr<DirectX::EffectFactory> boomerangFx = std::make_unique<DirectX::EffectFactory>(device);
	boomerangFx->SetDirectory(L"Resources/Models");
	// �u�u�[�������v���f�������[�h����
	m_boomerangModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Boomerang.cmo", *boomerangFx);

	// ���\�[�X�f�B���N�g����ݒ肷��
	std::unique_ptr<DirectX::EffectFactory> floorFx = std::make_unique<DirectX::EffectFactory>(device);
	floorFx->SetDirectory(L"Resources/Models");
	// �u���v���f�������[�h����
	m_floorModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Floor.cmo", *floorFx);

	// ���\�[�X�f�B���N�g����ݒ肷��
	std::unique_ptr<DirectX::EffectFactory> skyFx = std::make_unique<DirectX::EffectFactory>(device);
	skyFx->SetDirectory(L"Resources/Models");
	// �u��v���f�������[�h����
	m_skyModel = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Sky.cmo", *skyFx);

	// ���\�[�X�f�B���N�g����ݒ肷��
	std::unique_ptr<DirectX::EffectFactory> tree1Fx = std::make_unique<DirectX::EffectFactory>(device);
	tree1Fx->SetDirectory(L"Resources/Models");
	// �u�؂P�v���f�������[�h����
	m_tree1Model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Tree1.cmo", *tree1Fx);

	// ���\�[�X�f�B���N�g����ݒ肷��
	std::unique_ptr<DirectX::EffectFactory> rockFx = std::make_unique<DirectX::EffectFactory>(device);
	rockFx->SetDirectory(L"Resources/Models");
	// �u��v���f�������[�h����
	m_rockModel      = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Rock.cmo", *rockFx);



}
