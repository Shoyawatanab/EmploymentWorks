#pragma once
#include"GameBase/Actor.h"

class PlayerStateMachine;
class PlaySceneCamera;
class RigidbodyComponent;
class PlayerModel;
class AnimatorComponent;

class Player2 : public Actor
{
public:
	//プレイシーンカメラの取得
	PlaySceneCamera* GetPlaySceneCamera() { return m_playSceneCamera; }
	//プレイシーンカメラのセット
	void SetPlaySceneCamera(PlaySceneCamera* camera) { m_playSceneCamera = camera; }
	//モデルの取得
	PlayerModel* GetPlayerModel() { return m_model; }


public:
	//コンストラクタ
	Player2(Scene* scene);
	//デストラクタ
	~Player2() override ;
	//オブジェクト別の更新処理
	void UpdateActor(const float& deltaTime) override;

	//当たった時に呼び出される
	void OnCollisionEnter(ColliderComponent* collider);

	//当たり続けているときの呼び出される
	void OnCollisionStay(ColliderComponent* collider);


private:
	//ステートマシン
	std::unique_ptr<PlayerStateMachine>  m_stateMachine;
	//プレイシーンカメラ
	PlaySceneCamera* m_playSceneCamera;
	//重力
	RigidbodyComponent* m_rigidBody;
	//プレイヤモデル
	PlayerModel* m_model;
	//アニメーション
	AnimatorComponent* m_animation;

};