/*
	�N���X��     : PlayerRightArm
	����         : �v���C���̉E�r���f��
	�⑫�E���ӓ_ :
*/
#pragma once
#include "Game/Player/PlayerParts.h"


// �u�C���v�N���X���`����
class PlayerRightArm : public PlayerParts
{
private :

	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "RightArm";

public:
	//�R���X�g���N�^
	PlayerRightArm(Scene* scene);
	//�f�X�g���N�^
	~PlayerRightArm() override;



};

