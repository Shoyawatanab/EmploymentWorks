/*
	�N���X��     : PlayerLeftArm
	����         : �v���C���̍��r���f��
	�⑫�E���ӓ_ :
*/
#pragma once
#include "Game/Player/PlayerParts.h"




// �u�C���v�N���X���`����
class PlayerLeftArm : public PlayerParts
{
private:
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "LeftArm";

public:
	//�R���X�g���N�^
	PlayerLeftArm(Scene* scene);
	//�f�X�g���N�^
	~PlayerLeftArm() override;



};

