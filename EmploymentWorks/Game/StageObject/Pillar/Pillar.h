/*
	@file	Pillar.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/CollisiionManager.h"
#include "Game/Interface/IStateMachine.h"
#include "Game/Entities/MoveEntity.h"

// 前方宣言
class CommonResources;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Pillar : public MoveEntity
{
public:

	DirectX::SimpleMath::Vector3 GetInitialScale() { return m_initialScale; }
	
	IState* GetCurrentState() { return m_currentState; }




public:
	Pillar(CommonResources* resources);


	//デストラクタ
	~Pillar() override;

	//IObject
		//初期化
	void Initialize() override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;


	//ICollisionObject
	//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Stage; };
	//当たり判定クラスに登録
	void  AddCollision(CollisionManager* collsionManager) override;

	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//当たり判定の種類の取得
	const CollisionType GetCollisionType() override { return CollisionType::AABB; }
	//押し出しをするかどうか
	const bool GetIsExtrusion() override { return false; };
	//当たり判定を行わないタグ
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::Stage}
		};
	}


	//状態の変更
	void ChangeState(IState* nextState);



private:


	DirectX::SimpleMath::Vector3 m_initialScale;

	//現在の状態
	IState* m_currentState;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;





};
