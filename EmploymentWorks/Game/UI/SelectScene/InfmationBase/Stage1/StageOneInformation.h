/*
	�N���X��     : StageOneInformation
	����         : �Z���N�g�V�[���̉E�̏��(�X�e�[�W�P��)
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"

class Canvas;

class StageOneInformation : public Actor
{
public:

	static constexpr DirectX::SimpleMath::Vector3 BIRD_ONE_POSITION = { -100, 0, 0 };
	static constexpr DirectX::SimpleMath::Vector3 BIRD_TWO_POSITION = {100, 0, 0 };

public:
	//�R���X�g���N
	StageOneInformation(Canvas* canvas);
	//�f�X�g���N�^
	~StageOneInformation() override;


};

