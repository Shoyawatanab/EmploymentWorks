#pragma once
#include "GameBase/Actor.h"


class BirdEnemy;
class BirdEnemyBulletStateMachine;


class  BirdEnemyBullet : public Actor
{
public:
	//コンストラク
	BirdEnemyBullet(Scene* scene, BirdEnemy* birdEnemy);
	//デストラクタ
	~BirdEnemyBullet() override;

	//オブジェクト別の更新処理
	void UpdateActor(const float& deltaTime) override;

	//当たった時に呼び出される
	void OnCollisionEnter(ColliderComponent* collider) override;


private:

	//所有者
	BirdEnemy* m_birdEnemy;
	//ステートマシン
	std::unique_ptr<BirdEnemyBulletStateMachine> m_stateMachine;

};

