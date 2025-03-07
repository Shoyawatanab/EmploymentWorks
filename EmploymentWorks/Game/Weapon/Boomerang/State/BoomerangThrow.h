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

class BoomerangThrow : public IState
{

private:

	enum  class State
	{
		SplineCurve      //投げる
		, ChaseToPlayer   //返ってくる
	};

public:


	static constexpr float TARGET_LENGTH{ 5.0f };

public:
	//コンストラクタ
	BoomerangThrow() ;
	//デストラクタ
	~BoomerangThrow() override;

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

	float Lerp(float a, float b, float t);
	//スプライン曲線
	void SplineCurve(const float& elapsedTime);
	
	void ChaseToPlayer(const float& elapsedTime);

	
	//回転
	void Rotation(const float& elapsedTime);

	void ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec);



private:
	// 共通リソース
	CommonResources* m_commonResources;
	//ブーメラン
	Boomerang* m_boomerang;

	Player* m_player;


	TargetMarker* m_targetMarker;

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
	DirectX::SimpleMath::Quaternion m_horizontalRotation;

	DirectX::SimpleMath::Quaternion m_initialRotation;
};