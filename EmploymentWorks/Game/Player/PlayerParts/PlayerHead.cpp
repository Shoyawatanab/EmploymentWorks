#include "pch.h"
#include "PlayerHead.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/PlayerPartss.h"
#include "Game/Params.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
PlayerHead::PlayerHead(Scene* scene)
	:
	PlayerParts(scene, PARTS_NAME,"PlayerHead")
{
	//�傫��
	GetTransform()->SetScale(Params::PLAYER_HEAD_SCALE);
	//�ʒu���
	GetTransform()->Translate(Params::PLAYER_HEAD_POSITION);
	//��]
	GetTransform()->SetRotate(Params::PLAYER_HEAD_ROTATION);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerHead::~PlayerHead()
{
}



