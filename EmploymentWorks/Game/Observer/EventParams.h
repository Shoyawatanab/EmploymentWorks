#pragma once
struct EventParams
{

public:

	//�C�x���g�̎��
	enum class EventType
	{
		BoomerangGetReady    //�u�[���������\����
		, BoomerangGetReadyEnd  //�u�[�������̍\�����I���
		, BoomerangThrow      //�u�[�������𓊂���
		, GetBoomerang        //�u�[�������̎擾
		, GameClear
		, GameOver
		, DefeatedAllEnemies  // �S�Ă̓G��|������
		, PlayerDamage
		, BossBeamAttackEnd
		, CreateExplosion
		, CreateParticle  
		, CreateHitEffect
		,BossBeamHit  

	};

	//����������ꍇ�͑Ή������\���̂����
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