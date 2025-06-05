/*
* プレイヤクラス　
*/

#pragma once
#include"GameBase/Actor.h"



class BossEnemy : public Actor //, public IObserver<GamePlayMessageType> , public IObserver<EnemyMessageType>
{
public:

public:
	//コンストラクタ
	BossEnemy(Scene* scene);
	//デストラクタ
	~BossEnemy() override;

	//オブジェクト別の更新処理
	void UpdateActor(const float& deltaTime) override;

	//当たった時に呼び出される
	void OnCollisionEnter(ColliderComponent* collider);

	//当たり続けているときの呼び出される
	void OnCollisionStay(ColliderComponent* collider);

	//衝突が終了したときに呼び出される
	void OnCollisionExit(ColliderComponent* collider);


//
////通知時に呼ばれる関数
//	void Notify(const Telegram<GamePlayMessageType>& telegram)  override;
//
//	void Notify(const Telegram<EnemyMessageType>& telegram)  override;

private:




	



};


