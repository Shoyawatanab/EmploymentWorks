#include "pch.h"
#include "PlayerModel.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Player/PlayerPartss.h"
#include "GameBase/Component/Transform/Transform.h"
#include "Game/Params.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
PlayerModel::PlayerModel(Scene* scene)
	:
	ModelBase(scene)
{

	//Body�̍쐬
	auto body = GetScene()->AddActor<PlayerBody>(GetScene());
	body->GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(0, -0.6f, 0));
	//�e�̓o�^
	body->GetTransform()->SetParent(GetTransform());
	//�q�����f�����擾
	auto parts = body->GetAllDescendants();
	//�q�����f�����p�[�c�ɓo�^
	AddParts(parts);


}

/// <summary>
/// �ŃX�g�����O
/// </summary>
PlayerModel::~PlayerModel()
{
}


