#pragma once
//イベントの種類
enum class GameMessageType
{
	None = -1
	, BoomerangGetReady    //ブーメランを構える
	, BoomerangGetReadyEnd  //ブーメランの構えを終わる
	, BoomerangThrow      //ブーメランを投げる
	, GetBoomerang        //ブーメランの取得
	, GameClear
	, GameOver
	, DefeatedAllEnemies  // 全ての敵を倒したら
	, PlayerDamage
	, BossBeamAttackEnd
	, CreateExplosion
	, CreateParticle  
	, CreateHitEffect
	,CreateChageEffect
	, BossBeamHit  
	,ChangeBoomerangThrowState
	,MouseWheelUp
	,MouseWheelDown
	,BoomerangRecoverable  //ブーメランを回収可能
	,BoomerangNotRecoverable  //ブーメランを回収不可
	,CameraShake  //カメラを揺らす

};


enum class EnemyMessageType
{
	None
	,Walking
	,JumpAttack
	, BarrierDefense
	,BeamAttack
	, SwingDown
};

struct CreateHitEffectDatas
{
	DirectX::SimpleMath::Vector3 Position;
	DirectX::SimpleMath::Vector3 Scale;
	int Damage;
};

struct CreateChargeEffectDatas
{
	DirectX::SimpleMath::Vector3 Position;
	DirectX::SimpleMath::Vector3 Scale;

};


struct  UnknownDataTwo
{
	void* data1;
	void* data2;
};

struct  UnknownDataThree
{
	void* data1;
	void* data2;
	void* data3;
};




/*
	CreateHitEffectDatas
		data1が座標
	　　data2が大きさ
		data3がダメージ


*/




