#include "pch.h"
#include "BossEnemyParts.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="modelName">���f����</param>
BossEnemyParts::BossEnemyParts(Scene* scene, std::string partsName, std::string modelName)
	:
	ModelPartsBase(scene,partsName,modelName)
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyParts::~BossEnemyParts()
{
}
