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
	
	GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(640, 360,0));
	GetTransform()->SetScale(DirectX::SimpleMath::Vector3(0.2f, 0.2f, 0));


	SetActive(false);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PickUpUI::~PickUpUI()
{
}
