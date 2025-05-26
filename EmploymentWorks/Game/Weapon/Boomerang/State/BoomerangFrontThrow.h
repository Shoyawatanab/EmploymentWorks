/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "Game/Interface/IState.h"

class Boomerang;
class Player;
class TargetMarker;

namespace WataLib
{
	class TPS_Camera;
}

class BoomerangFrontThrow : public IState
{

private:
	//状態
	enum  class State
	{
		SPINECURVE      //投げる
		, CHASE_TO_PLAYER   //返ってくる
	};

public:


	static constexpr float TARGET_LENGTH{ 5.0f };

public:
	//コンストラクタ
	BoomerangFrontThrow(Boomerang* boomerang) ;
	//デストラクタ
	~BoomerangFrontThrow() override;

	//初期化
	void Initialize(CommonResources* resources) ;
	// 更新する
	void Update(const float& elapsedTime) override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

	//ターゲットを追いかける
	bool ChaseToTarget(const float& elapsedTime);

	
	//回転
	void Rotation(const float& elapsedTime);
	//回転情報の切り替え
	void ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec);



private:
	// 共通リソース
	CommonResources* m_commonResources;
	//ブーメラン
	Boomerang* m_boomerang;
	//プレイヤ
	Player* m_player;
	//ターゲットマーカー
	TargetMarker* m_targetMarker;
	//カメラ
	WataLib::TPS_Camera* m_tpsCamera;

	//経過時間
	float m_totalTime;
	//状態
	State m_state;
	//ターゲット座標
	DirectX::SimpleMath::Vector3 m_targetPosistion;

};