/*
	@file	BirdEnemyBeam.h
	@brief	鳥の敵のビーム
*/
#pragma once
#include "Game/Enemys/BirdEnemy/Beam/BeamState/BirdEnemyBeamStateMachine.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeamEnergyBall.h"

#include "Game/Entities/BaseEntity.h"
// 前方宣言
class CommonResources;
class BirdEnemy;
class Player;
class CollisionManager;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BirdEnemyBeam : public BaseEntity
{

public:
	//インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


public:
	//ターゲットの取得
	const DirectX::SimpleMath::Vector3& GetTarget() { return m_target; }
	//ターゲットの登録
	void SetTarget(const DirectX::SimpleMath::Vector3& target) { m_target = target; }
	//ステートマシーンの取得
	BirdEnemyBeamStateMachine* GetStateMahine() { return m_stateMachine.get(); }
	//
	BirdEnemyBeamEnergyBall* GetBeamEnergyBall() { return m_energyBall.get(); }

public:
	//コンストラクタ
	BirdEnemyBeam(CommonResources* resources, BirdEnemy* enemy);
	//デストラクタ
	~BirdEnemyBeam() override;	
	//初期化
	void Initialize() override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;

	void UpdateBirdEnemyBeamPosition();
	//コリジョンに追加
	void  AddCollision(CollisionManager* collsionManager);

private:

	// モデル
	std::unique_ptr<DirectX::Model> m_model;
	//ターゲット
	DirectX::SimpleMath::Vector3 m_target;
	//鳥の敵
	BirdEnemy* m_enemy;
	//プレイヤ
	Player* m_player;
	//エネルギー弾
	std::unique_ptr<BirdEnemyBeamEnergyBall> m_energyBall;
	//ステートマシーン
	std::unique_ptr<BirdEnemyBeamStateMachine> m_stateMachine;

};
