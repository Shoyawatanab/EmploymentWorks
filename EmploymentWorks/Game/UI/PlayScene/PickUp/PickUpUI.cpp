/*
	�N���X��     : PickUpUI
	����         : ����\UI
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "PickUpUI.h"
#include "Game/Component/Components.h"


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
PickUpUI::PickUpUI(Canvas* canvas)
	:
	Image(canvas,"F")
{
	
	GetTransform()->SetPosition(POSITION);
	GetTransform()->SetScale(SCALE);


	SetActive(false);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PickUpUI::~PickUpUI()
{
}
