/*
	�N���X��     : StageOneInformation
	����         : �Z���N�g�V�[���̉E�̏��(�X�e�[�W�P��)
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "StageOneInformation.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "GameBase/UI/Image.h"



/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
StageOneInformation::StageOneInformation(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	using namespace DirectX::SimpleMath;



	//�X�e�[�W�P�̏��
	auto birdEnemy1 = GetScene()->AddActor<Image>(canvas, "BirdEnemy");
	birdEnemy1->GetTransform()->SetPosition(BIRD_ONE_POSITION);
	birdEnemy1->GetTransform()->SetParent(GetTransform());

	auto birdEnemy2 = GetScene()->AddActor<Image>(canvas, "BirdEnemy");
	birdEnemy2->GetTransform()->SetPosition(BIRD_TWO_POSITION);
	birdEnemy2->GetTransform()->SetParent(GetTransform());


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageOneInformation::~StageOneInformation()
{
}

