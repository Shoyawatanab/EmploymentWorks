/*
	�N���X��     : StageBackGraund
	����         : �Z���N�g�V�[���̃X�e�[�WUI�̔w�i
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "StageBackGraund.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Fade/FadeManager.h"
#include "Game/GlobalGameData.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
StageBackGraund::StageBackGraund(Canvas* canvas)
	:
	Image(canvas, "StageBackGraund")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);




}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageBackGraund::~StageBackGraund()
{
}

