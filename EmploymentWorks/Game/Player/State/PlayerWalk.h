/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "Game/Interface/IState.h"

class PlayerStateMachine;
class Player2;
class RigidbodyComponent;


class PlayerWalk : public IState
{
public:
	//コンストラクタ
	PlayerWalk(PlayerStateMachine* stateMachine, Player2* player);
	//デストラクタ
	~PlayerWalk() override;
	// 更新する
	void Update(const float& deltatime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

private:
	//移動
	void Move(const float& deltatime);
	//回転
	void Rotate(const float& deltatime);
private:
	//プレイヤ
	Player2* m_player;
	//ステートマシーン
	PlayerStateMachine* m_stateMahine;
	//リジットボディー
	RigidbodyComponent* m_rigidbody;

	//移動量
	DirectX::SimpleMath::Vector3 m_moveDirection;


};