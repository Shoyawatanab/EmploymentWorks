#pragma once
#include "GameBase/Action/ActionController.h"
#include "GameBase/Actor.h"

#include "Game/Enemies/BossEnemy/Action/Orientation/OrientationAction.h"


// �O���錾
class CommonResources;
class Player;
class BossEnemy;



class OrientationActionController : public ActionController
{

public:



public:
	//�R���X�g���N�^
	OrientationActionController(BossEnemy* bossEnemy
		, Player* player);
	//�f�X�g���N�^
	~OrientationActionController()override;




private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	//��]
	std::unique_ptr<OrientationAction> m_orientation;


};
#pragma once
