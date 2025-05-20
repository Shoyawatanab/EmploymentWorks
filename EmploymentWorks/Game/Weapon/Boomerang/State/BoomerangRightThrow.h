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

class BoomerangRightThrow : public IState
{

private:

	enum  class State
	{
		SPINECURVE      //投げる
		, CHASE_TO_PLAYER   //返ってくる
		, PASSING_THROUGH //通り抜け
	};

public:


	static constexpr float TARGET_LENGTH{ 5.0f };

public:
	//コンストラクタ
	BoomerangRightThrow() ;
	//デストラクタ
	~BoomerangRightThrow() override;

	//初期化
	void Initialize(CommonResources* resources) override;
	// 更新する
	void Update(const float& elapsedTime) override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

	//必要なポインタの登録
	void AddPointer(Boomerang* boomerang,Player* player, TargetMarker* targetMarker, WataLib::TPS_Camera* tpsCamera);

	//スプライン曲線の基準点の作成
	void CreateSplineCurvePositon();

	//スプライン曲線
	void SplineCurve(const float& elapsedTime);
	//プレイヤを追いかける
	void ChaseToPlayer(const float& elapsedTime);
	//通過
	void PassingThrough(const float& elapsedTime);
	
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

	//スプライン曲線の座標
	std::vector<DirectX::SimpleMath::Vector3> m_splineCurvePosition;
	//添え字
	int m_index;
	//経過時間
	float m_totalTime;
	//状態
	State m_state;
	//回転の情報
	std::pair<DirectX::SimpleMath::Quaternion, DirectX::SimpleMath::Quaternion> m_rotationDatas;
	//横回転
	DirectX::SimpleMath::Quaternion m_horizontalRotation;
	//初期回転
	DirectX::SimpleMath::Quaternion m_initialRotation;
	//動く方向
	DirectX::SimpleMath::Vector3 m_moveDirection;

};