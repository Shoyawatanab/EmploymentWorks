/*
	�N���X��     : PlayerLeftFeet
	����         : �v���C���̍������f��
	�⑫�E���ӓ_ :
*/
#pragma once
#include "Game/Player/PlayerParts.h"



// �u�C���v�N���X���`����
class PlayerLeftFeet : public PlayerParts
{
private:

	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "LeftFeet";

public:
	//�R���X�g���N�^
	PlayerLeftFeet(Scene* scene);
	//�f�X�g���N�^
	~PlayerLeftFeet() override;




};

