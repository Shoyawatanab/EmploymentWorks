#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"

class Canvas;
class DamageCount;

class DamageCountFactory : public Actor , public IObserver
{
public:
	//�ő吶����
	static constexpr int MAX = 1;

public:
	//�R���X�g���N�^
	DamageCountFactory(Canvas* canvas);
	//�f�X�g���N�^
	~DamageCountFactory() override;

	//�ʒm���ɌĂяo�����
	void Notify(MessageType type, void* datas) override;

private:

	std::vector<DamageCount*> m_damageCount;

};
