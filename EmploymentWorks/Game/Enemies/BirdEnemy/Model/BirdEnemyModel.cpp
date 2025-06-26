#include "pch.h"
#include "BirdEnemyModel.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Enemies/BirdEnemy/BirdEnemyPartss.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
BirdEnemyModel::BirdEnemyModel(Scene* scene)
	:
	ModelBase(scene)
{
	//BODY�̍쐬
	auto body = GetScene()->AddActor<BirdEnemyBody>(GetScene());
	//�e�q�֌W������
	body->GetTransform()->SetParent(GetTransform());

	//�q�����f�����擾
	auto parts = body->GetAllDescendants();
	//�q�����f�����p�[�c�ɓo�^
	AddParts(parts);
	


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyModel::~BirdEnemyModel()
{
}
