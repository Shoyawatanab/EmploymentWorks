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
		,BossBeamHit  

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