/*
	@file	BirdEnemyFeather.cpp
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
#include "BirdEnemyFeather.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="parent">�e</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
BirdEnemyFeather::BirdEnemyFeather(CommonResources* resources, 
	CharacterEntity* parent, 
	DirectX::SimpleMath::Vector3 scale, 
	DirectX::SimpleMath::Vector3 position, 
	DirectX::SimpleMath::Quaternion rotation)
	: 
	BirdEnemyPartsBase(resources, parent, PARTSNAME, scale, position, rotation)
{
}

/// <summary>
/// �f�X�g���N
/// </summary>
BirdEnemyFeather::~BirdEnemyFeather()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void BirdEnemyFeather::Initialize()
{



	// ���f����ǂݍ���
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BirdEnemyFeather");

	BirdEnemyPartsBase::SetModel(model);

	BirdEnemyPartsBase::Initialize();


}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyFeather::Update(const float& elapsedTime)
{

	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}
	
	BirdEnemyPartsBase::Update(elapsedTime);

}

