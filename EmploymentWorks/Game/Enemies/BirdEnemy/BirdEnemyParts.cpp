#include "pch.h"
#include "BirdEnemyParts.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="modelName">���f����</param>
BirdEnemyPars::BirdEnemyPars(Scene* scene, const std::string& partsName, const std::string& modelName)
	:
	ModelPartsBase(scene,partsName,modelName)
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyPars::~BirdEnemyPars()
{
}
