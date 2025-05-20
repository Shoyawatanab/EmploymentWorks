/*
* プレイヤクラス　
*/

#pragma once
#include "CompositeEntity.h"

//前方宣言
class EnemyManager;

class EnemyEntity : public CompositeEntity
{
public:

	//敵マネージャーの取得
	EnemyManager* GetEnemyManager() { return m_enemyMangaer; }
	 
public:
	//コンストラク
	EnemyEntity(CommonResources* resources
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//デストラクタ
	~EnemyEntity() override;


	//BaseEntity
	//初期化
	void Initialize();
	//更新処理
	void  Update(const float& elapsedTime)  override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	//CollisionEntity
		//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//敵マネージャーの登録
	void SetManager(EnemyManager* enemyManager);

private:

	//敵マネージャー
	EnemyManager* m_enemyMangaer;

};


