/*
	�N���X��     : BirdEnemyHP
	����         : ���G��HP��UI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;

class BirdEnemyHP : public Actor 
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITION{4, 5.0, 0};
	//�w�i�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 BACKGRAUND_SCALE{1, 0.9, 1};
	//���W
	static constexpr DirectX::SimpleMath::Vector3 HP_BAR_SCALE{1, 0.85, 1};
public:
	//�R���X�g���N�^
	BirdEnemyHP(Canvas* canvas);
	//�f�X�g���N�^
	~BirdEnemyHP() override ;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);


private:

	Image* m_backGraund;

	Image* m_hpBar;

};

