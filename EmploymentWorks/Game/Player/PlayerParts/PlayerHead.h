/*
* �v���C���̓��N���X
*/
#pragma once
#include "Game/Player/PlayerParts.h"


// �u�C���v�N���X���`����
class PlayerHead : public PlayerParts
{
private:
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "Head";

public:
	//�R���X�g���N�^
	PlayerHead(Scene* scene);
	//�f�X�g���N�^
	~PlayerHead() override;

};

