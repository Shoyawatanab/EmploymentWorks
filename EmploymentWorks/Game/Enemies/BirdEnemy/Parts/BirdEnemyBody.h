/*
	�N���X��     : BirdEnemyBody
	����         : ���G�̑�
	�⑫�E���ӓ_ :
*/
#pragma once
#include "Game/Enemies/BirdEnemy/BirdEnemyParts.h"


class BirdEnemyBody : public BirdEnemyPars
{
public:

	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "Body";

public:
	//�R���X�g���N
	BirdEnemyBody(Scene* scene);
	//�f�X�g���N�^
	~BirdEnemyBody() override;


};



