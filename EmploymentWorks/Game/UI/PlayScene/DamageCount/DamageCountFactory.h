#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"

class Canvas;
class DamageCount;

class DamageCountFactory : public Actor , public IObserver
{
public:
	//最大生成数
	static constexpr int MAX = 1;

public:
	//コンストラクタ
	DamageCountFactory(Canvas* canvas);
	//デストラクタ
	~DamageCountFactory() override;

	//通知時に呼び出される
	void Notify(MessageType type, void* datas) override;

private:

	std::vector<DamageCount*> m_damageCount;

};
