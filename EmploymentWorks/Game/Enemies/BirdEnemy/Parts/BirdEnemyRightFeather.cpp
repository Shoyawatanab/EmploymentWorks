#include "pch.h"
#include "BirdEnemyRightFeather.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
BirdEnemyRightFeather::BirdEnemyRightFeather(Scene* scene)
	:
	BirdEnemyPars(scene,PARTS_NAME,"BirdEnemyFeather")
{

	//�ʒu���
	GetTransform()->Translate(Params::BIRDENEMY_RIGHTFEATHER_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BIRDENEMY_RIGHTFEATHER_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BIRDENEMY_RIGHTFEATHER_ROTATION);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyRightFeather::~BirdEnemyRightFeather()
{
}