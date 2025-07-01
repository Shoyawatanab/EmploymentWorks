#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Canvas;
class DamageCount;

class DamageCountFactory : public Actor , public IObserver<SceneMessageType>
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
	void Notify(SceneMessageType type, void* datas) override;

private:

	std::vector<DamageCount*> m_damageCount;

};
