#pragma once
//ゲームの種類
enum class GameMessageType
{
	None = -1
	, BOOMERANG_GET_READY    //ブーメランを構える
	, BOOMERANG_GET_READY_END  //ブーメランの構えを終わる
	, BOOMERANG_THTROW      //ブーメランを投げる
	, GET_BOOMERANG        //ブーメランの取得
	, GAME_CLEAR
	, GAME_OVER
	, DEFEATED_All_ENEMIES  // 全ての敵を倒したら
	, PLAYER_DAMAGE
	, BOSS_BEAM_ATTACK_END
	, CREATE_EXPLOSION
	, CREATE_PARTICLE  
	, CREATE_HIT_EFFECT
	, CREATE_CHAGE_EFFECT
	, BOSS_BEAM_HIT  
	,CHARGE_BOOMERANG_THROW_STATE
	,MOUSE_WHEEL_UP
	,MOUSE_WHEEL_DOWN
	,BOOMERANG_RECOVERBLE  //ブーメランを回収可能
	, BOOMERANG_NOT_RECOVERBLE  //ブーメランを回収不可
	,CAMERA_SHAKE  //カメラを揺らす

};

//敵のイベントの種類
enum class EnemyMessageType
{
	NONE
	,WALKING
	,JUMP_ATTACK
	, BARRIER_DEFENSE
	, BEAM_ATTACK
	, SWING_DOWN
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




