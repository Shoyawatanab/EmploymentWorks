/*
	�N���X��     : PlayerRightFeet
	����         : �v���C���̉E�����f��
	�⑫�E���ӓ_ :
*/
#pragma once
#include "Game/Player/PlayerParts.h"



// �u�C���v�N���X���`����
class PlayerRightFeet : public PlayerParts
{
private:

	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "RightFeet";

public:
	//�R���X�g���N�^
	PlayerRightFeet(Scene* scene);
	//�f�X�g���N�^
	~PlayerRightFeet() override;



};

