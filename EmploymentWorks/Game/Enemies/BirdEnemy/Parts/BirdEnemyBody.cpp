#include "pch.h"
#include "BirdEnemyBody.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Enemies/BirdEnemy/BirdEnemyPartss.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
BirdEnemyBody::BirdEnemyBody(Scene* scene)
	:
	BirdEnemyPars(scene,PARTS_NAME,"BirdEnemyBody")
{
	//���H�̍쐬
	auto leftFeather = GetScene()->AddActor<BirdEnemyLeftFeather>(GetScene());
	//�e�q�֌W�����ԁ@
	leftFeather->SetParent(this);
	//�E�H�̍쐬
	auto rightFeather = GetScene()->AddActor<BirdEnemyRightFeather>(GetScene());
	//�e�q�֌W������
	rightFeather->SetParent(this);

	//�ʒu���
	GetTransform()->Translate(Params::BIRDENEMY_BODY_POSITION);
	//�傫��
	GetTransform()->SetScale(Params::BIRDENEMY_BODY_SCALE);
	//��]
	GetTransform()->SetRotate(Params::BIRDENEMY_BODY_ROTATION);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBody::~BirdEnemyBody()
{
}
