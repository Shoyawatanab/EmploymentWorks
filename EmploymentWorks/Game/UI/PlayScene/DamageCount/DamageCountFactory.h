/*
	�N���X��     : DamageCountFactory
	����         : �_���[�WUI�̍쐬�N���XI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class DamageCount;

class DamageCountFactory : public Actor
{
public:
	//�ő吶����
	static constexpr int MAX = 10;

public:
	//�R���X�g���N�^
	DamageCountFactory(Canvas* canvas);
	//�f�X�g���N�^
	~DamageCountFactory() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);

private:

	//�_���[�WUI�z��
	std::vector<DamageCount*> m_damageCount;

};
