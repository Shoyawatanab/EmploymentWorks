/*
	�N���X��     : BossDeathActionController
	����         : �{�X�G�̓|�����Ƃ��̃R���g���[���[
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Action/ActionController.h"

class BossDeathAction;
class BossDeathEndAction;

class BossEnemy;


class BossDeathActionController : public ActionController
{
public:
	//�R���X�g���N
	BossDeathActionController(BossEnemy* bossEnemy);
	//�f�X�g���N�^
	~BossDeathActionController()override;

private:
	//�ʏ�
	std::unique_ptr<BossDeathAction> m_idle;
	//�I��
	std::unique_ptr<BossDeathEndAction> m_end;
};
