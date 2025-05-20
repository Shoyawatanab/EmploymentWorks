/*
	@file	Beam.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/CollisiionManager.h"
#include "Game/Interface/IStateMachine.h"
#include "Game/Entities/BaseEntity.h"

// 前方宣言
class CommonResources;
class BeamEnergyBall;
class BeamChargeEffect;
class BeamRays;
class BeamStateMachine;
class Player;
class BossEnemy;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Beam : public BaseEntity
{
public:

	//チャージエフェクトの大きさ
	static constexpr DirectX::SimpleMath::Vector3 EFFECT_SCALE{ 0.1f,0.1f,0.1f };

public:

	//ビームの取得
	BeamEnergyBall* GetBeamEnergyBall() { return m_energyBall.get(); }
	//エフェクトの取得
	std::vector<std::unique_ptr< BeamChargeEffect>>&  GetBeamChargeEffect() { return m_chargeEffect; }
	//光線の取得
	BeamRays* GetBeamRays() { return m_rays.get(); }



public:
	//コンストラク
	Beam(CommonResources* resources);
	//デストラクタ
	~Beam() override;


	//初期化
	void Initialize() override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;

	//クラスに必要な情報（ポインタ）を登録する
	void AddPointer(BossEnemy* bossEnemy,Player* player);

	//当たり判定の追加
	void AddCollionManager(CollisionManager* collsionManager) ;
	//パーティクル生成
	void CreateParticle();
	//パーティクルの削除
	void RegistrationDeleteParticle(BeamChargeEffect* effect);



private:
	//エネルギー弾
	std::unique_ptr<BeamEnergyBall> m_energyBall;
	//予備動作時間
	float m_preliminaryActitonTime;
	//チャージエフェクト
	std::vector<std::unique_ptr<BeamChargeEffect>> m_chargeEffect;
	//削除するエフェクト
	std::vector<BeamChargeEffect*> m_deleteChargeEffect;
	//光線
	std::unique_ptr<BeamRays> m_rays;
	//プレイヤ
	Player* m_player;

};
