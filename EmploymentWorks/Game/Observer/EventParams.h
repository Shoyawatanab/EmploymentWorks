#pragma once
struct EventParams
{

public:

	//イベントの種類
	enum class EventType
	{
		BoomerangGetReady    //ブーメランを構える
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

	};

	//引数がある場合は対応した構造体を作る
	struct CreateExplosionDatas
	{
		DirectX::SimpleMath::Vector3 Position;
		DirectX::SimpleMath::Vector3 Scale;

	};

	struct CreateParticleDatas
	{
		DirectX::SimpleMath::Vector3 Position;
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

	struct  ChangeBoomerangThrowStateDatas
	{

		int State;

	};

};


/*
		BoomerangGetReady
		{
			Sbu  PlayerAttack
			Ob PlayerUsually , TargetMarker
		}
		BoomerangGetReadyEnd 
		{
			
		}
		BoomerangThrow      
		{
			
		}
		GetBoomerang        
		{
			
		}
		GameClear
		{
			
		}
		GameOver
		{
			
		}
		DefeatedAllEnemies  
		{
			
		}
		PlayerDamage
		{
			
		}
		BossBeamAttackEnd
		{
			
		}
		CreateExplosion
		{

		}
*/