/*
	�N���X��     : StageTwoImage
	����         : �Z���N�g�V�[���̃X�e�[�W�Q�̉摜
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "StageTwoImage.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
StageTwoImage::StageTwoImage(Canvas* canvas)
	:
	Image(canvas, "Stage2")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageTwoImage::~StageTwoImage()
{
}


