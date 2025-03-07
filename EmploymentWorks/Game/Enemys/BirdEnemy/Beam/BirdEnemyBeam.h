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
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


public:

	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }
 
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }
	

	BirdEnemyBeamStateMachine* GetStateMahine() { return m_stateMachine.get(); }

	BirdEnemyBeamEnergyBall* GetBeamEnergyBall() { return m_energyBall.get(); }

public:
	BirdEnemyBeam(CommonResources* resources, Player* player, BirdEnemy* enemy);

	//デストラクタ
	~BirdEnemyBeam() override;

	//IObject
		//初期化
	void Initialize() override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;

	void UpdateBirdEnemyBeamPosition();

	void  AddCollision(CollisionManager* collsionManager);

private:



	// モデル
	std::unique_ptr<DirectX::Model> m_model;
	DirectX::SimpleMath::Vector3 m_target;

	BirdEnemy* m_enemy;
	Player* m_player;
	std::unique_ptr<BirdEnemyBeamEnergyBall> m_energyBall;
	std::unique_ptr<BirdEnemyBeamStateMachine> m_stateMachine;

};
