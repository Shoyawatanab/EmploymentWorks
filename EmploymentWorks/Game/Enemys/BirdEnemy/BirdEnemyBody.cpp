/*
	@file	BirdEnemyBody.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/WataLib/GameResources.h"
#include <cassert>
#include "Game/CollisiionManager.h"
#include "BirdEnemyBody.h"
#include"Game/Enemys/BirdEnemy/BirdEnemyFeather.h"
#include "Game/Params.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="parent">�e</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
BirdEnemyBody::BirdEnemyBody(CommonResources* resources,
	CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale, 
	DirectX::SimpleMath::Vector3 position, 
	DirectX::SimpleMath::Quaternion rotation)
	:
	BirdEnemyPartsBase(resources, parent,PARTSNAME,scale,position,rotation)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBody::~BirdEnemyBody()
{
}

/// <summary>
/// ������
/// </summary>
void BirdEnemyBody::Initialize()
{

	using namespace DirectX::SimpleMath;


	// ���f����ǂݍ���
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BirdEnemyBody");

	BirdEnemyPartsBase::SetModel(model);
	//������
	BirdEnemyPartsBase::Initialize();

	//���H�̒ǉ�
	AddChild(std::make_unique<BirdEnemyFeather>(BaseEntity::GetCommonResources(),
		this,
		Params::BIRDENEMY_LEFTFEATHER_SCALE,
		Params::BIRDENEMY_LEFTFEATHER_POSITION,
		Params::BIRDENEMY_LEFTFEATHER_ROTATION));
	//�E�H�̒ǉ�
	AddChild(std::make_unique<BirdEnemyFeather>(BaseEntity::GetCommonResources(),
		this,
		Params::BIRDENEMY_RIGHTFEATHER_SCALE,
		Params::BIRDENEMY_RIGHTFEATHER_POSITION,
		Params::BIRDENEMY_RIGHTFEATHER_ROTATION));

}


/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyBody::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}



	BirdEnemyPartsBase::Update(elapsedTime);

}

