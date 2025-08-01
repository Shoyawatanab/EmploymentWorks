/*
	�N���X��     : BossEnemyLeftShoulder
	����         : �{�X�G�̍������f��
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "BossEnemyLeftShoulder.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/BossEnemyPartss.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="boss">�{�X</param>
BossEnemyLeftShoulder::BossEnemyLeftShoulder(Scene* scene, BossEnemy* boss)
	:
	BossEnemyParts(scene, PARTS_NAME
		, "BossEnemyShoulder"
		, Params::BOSSENEMY_LEFTSHOULDER_HP
		//, 10
		, Params::BOSSENEMY_LEFTSHOULDER_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_LEFTSHOULDER_SPHERE_COLLIDER_SIZE
		, boss)
{

	//�ȉ��ǉ����ʂ̍쐬
	//�uLeftArmJoint�v�𐶐�����
	auto leftArmJoint = GetScene()->AddActor<BossEnemyLeftArmJoint>(GetScene(), boss);
	leftArmJoint->SetParent(this);

	//�ʒu���
	GetTransform()->Translate(Params::BOSSENEMY_LEFTSHOULDER_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BOSSENEMY_LEFTSHOULDER_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BOSSENEMY_LEFTSHOULDER_ROTATION);



}

/// <summary>
/// �R���X�g���N
/// </summary>
BossEnemyLeftShoulder::~BossEnemyLeftShoulder()
{
}

/// <summary>
/// ���ʔj�󎞂̏���
/// </summary>
void BossEnemyLeftShoulder::PartsDestruction()
{

	//�e�q�֌W���Ȃ���
	//GetTransform()->SetParent(nullptr);


	////�d�͂̒ǉ�
	//auto rigidBody = GetComponent<RigidbodyComponent>();
	//rigidBody->SetActive(true);
	

	
}
