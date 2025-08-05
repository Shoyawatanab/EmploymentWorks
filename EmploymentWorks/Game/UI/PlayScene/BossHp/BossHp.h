/*
	�N���X��     : BossHp
	����         : �{�XHP��UI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;

class BossHp : public Actor 
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITION{640, 50.5, 0};
	//�w�i�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 BACKGRAUND_SCALE{1, 0.9, 0};
	//���W
	static constexpr DirectX::SimpleMath::Vector3 HP_BAR_SCALE{1, 0.85, 0};
public:
	//�R���X�g���N�^
	BossHp(Canvas* canvas);
	//�f�X�g���N�^
	~BossHp() override ;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);


private:

	Image* m_backGraund;

	Image* m_hpBar;

};

