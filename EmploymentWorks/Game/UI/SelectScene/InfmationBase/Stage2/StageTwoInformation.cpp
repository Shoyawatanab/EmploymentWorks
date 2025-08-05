/*
	�N���X��     : StageTwoInformation
	����         : �Z���N�g�V�[���̉E�̏��(�X�e�[�W2��)
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "StageTwoInformation.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "GameBase/UI/Image.h"


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
StageTwoInformation::StageTwoInformation(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	
	using namespace DirectX::SimpleMath;


	//�{�X�摜
	auto boss = GetScene()->AddActor<Image>(canvas, "BossEnemy");
	boss->GetTransform()->SetParent(GetTransform());


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageTwoInformation::~StageTwoInformation()
{
}



