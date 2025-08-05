/*
	�N���X��     : InformationBackGraund
	����         : �Z���N�g�V�[���̉E�̏��̔w�i
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "InformationBackGraund.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
InformationBackGraund::InformationBackGraund(Canvas* canvas)
	:
	Image(canvas, "SelectInfBase")
{
	using namespace DirectX::SimpleMath;

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITOIN);




}

/// <summary>
/// �f�X�g���N�^
/// </summary>
InformationBackGraund::~InformationBackGraund()
{
}

