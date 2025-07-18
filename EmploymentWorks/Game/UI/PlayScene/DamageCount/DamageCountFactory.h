/*
	クラス名     : DamageCountFactory
	説明         : ダメージUIの作成クラスI
	補足・注意点 :
*/
#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Canvas;
class DamageCount;

class DamageCountFactory : public Actor , public IObserver<SceneMessageType>
{
public:
	//最大生成数
	static constexpr int MAX = 10;

public:
	//コンストラクタ
	DamageCountFactory(Canvas* canvas);
	//デストラクタ
	~DamageCountFactory() override;

	//通知時に呼び出される
	void Notify(SceneMessageType type, void* datas) override;

private:

	//ダメージUI配列
	std::vector<DamageCount*> m_damageCount;

};
