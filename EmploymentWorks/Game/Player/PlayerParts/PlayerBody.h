/*
* �v���C���̑̃N���X
*/

#pragma once
#include "Game/Player/PlayerParts.h"



// �u�C���v�N���X���`����
class PlayerBody : public PlayerParts
{

private:

	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "Body";


public:
	//�R���X�g���N�^
	PlayerBody(Scene* scene);           //+Z�Ɍ����Ă���Ƃ��̉�]���
	//�f�X�g���N�^
	~PlayerBody() override;

	//void OnCollisionEnter(Collider* collider) override;

};

