#pragma once
//�C�x���g�̎��
enum class MessageType
{
	None = -1
	, BoomerangGetReady    //�u�[���������\����
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
	,CreateChageEffect
	, BossBeamHit  
	,ChangeBoomerangThrowState
	,MouseWheelUp
	,MouseWheelDown
	,BoomerangRecoverable  //�u�[������������\
	,BoomerangNotRecoverable  //�u�[������������s��

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
		data1�����W
	�@�@data2���傫��
		data3���_���[�W


*/




