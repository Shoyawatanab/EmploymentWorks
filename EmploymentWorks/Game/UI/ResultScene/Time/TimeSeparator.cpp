/*
	�N���X��     : TimeSeparator
	����         : ���U���g�V�[���̎���UI�̕��ƕb�̊Ԃ̓_��UI
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "TimeSeparator.h"
#include "Game/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas"></param>
TimeSeparator::TimeSeparator(Canvas* canvas)
	:
	Image(canvas,"Ten")
{

	GetTransform()->SetScale(SCALE);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TimeSeparator::~TimeSeparator()
{
}


