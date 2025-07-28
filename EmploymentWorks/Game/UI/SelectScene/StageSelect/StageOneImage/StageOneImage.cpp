/*
	�N���X��     : StageOneImage
	����         : �Z���N�g�V�[���̃X�e�[�W�P�̉摜
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "StageOneImage.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
StageOneImage::StageOneImage(Canvas* canvas)
	:
	Image(canvas, "Stage1")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);




}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageOneImage::~StageOneImage()
{
}

