/*
	�N���X��     : InformationBase
	����         : �Z���N�g�V�[���̉E�̏��̂܂Ƃ߃N���X
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "InformationBase.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Fade/FadeManager.h"
#include "Game/GlobalGameData.h"
#include "Game/UI/SelectScene/InfmationBase/BackGraund/InformationBackGraund.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
InformationBase::InformationBase(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	using namespace DirectX::SimpleMath;


	//�w�i
	GetScene()->AddActor<InformationBackGraund>(canvas);




}

/// <summary>
/// �f�X�g���N�^
/// </summary>
InformationBase::~InformationBase()
{
}

