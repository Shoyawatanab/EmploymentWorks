#include "pch.h"
#include "BirdEnemyLeftFeather.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
BirdEnemyLeftFeather::BirdEnemyLeftFeather(Scene* scene)
	:
	BirdEnemyPars(scene,PARTS_NAME,"BirdEnemyFeather")
{

	//�ʒu���
	GetTransform()->Translate(Params::BIRDENEMY_LEFTFEATHER_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BIRDENEMY_LEFTFEATHER_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BIRDENEMY_LEFTFEATHER_ROTATION);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyLeftFeather::~BirdEnemyLeftFeather()
{
}
