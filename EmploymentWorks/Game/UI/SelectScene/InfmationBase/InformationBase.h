/*
	�N���X��     : InformationBase
	����         : �Z���N�g�V�[���̉E�̏��̂܂Ƃ߃N���X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Button;

class InformationBase : public Actor
{
public:
	//�R���X�g���N
	InformationBase(Canvas* canvas);
	//�f�X�g���N�^
	~InformationBase() override;


};

