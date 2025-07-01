#include "pch.h"
#include "BossEnemyModel.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"
#include "GameBase/Component/Transform/Transform.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
BossEnemyModel::BossEnemyModel(Scene* scene, BossEnemy* boss)
	:
	ModelBase(scene)
{

	using namespace DirectX::SimpleMath;

	//Body�̍쐬
	auto body = GetScene()->AddActor<BossEnemyBottom>(GetScene(),boss);
	body->GetTransform()->SetParent(GetTransform());
	//�q�����f�����擾
	auto parts = body->GetAllDescendants();
	//�q�����f�����p�[�c�ɓo�^
	AddParts(parts);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyModel::~BossEnemyModel()
{
}


