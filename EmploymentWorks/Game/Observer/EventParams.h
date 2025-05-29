#pragma once
//ゲームの種類
enum class GamePlayMessageType
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
	,NEXT_SCENE  //次のシーンに
	,CHANGE_THROW_COUNT                      //ブーメランをまとめてなげるかどうかの切り替え


};

//敵のイベントの種類
enum class EnemyMessageType
{
	NONE
	, IDLING            //通常状態
	, WALKING           //歩き
	, JUMP_ATTACK	    //ジャンプ攻撃
	, BARRIER_DEFENSE   //バリア防御
	, BEAM_ATTACK	    //ビーム攻撃
	, SWING_DOWN	    //振り下ろし攻撃
	, MOVEING           //動く
};

//パーツの通知の種類　敵　プレイヤなど混合　分けたい
enum class PartMessageType
{
	PART_DESTRUCTION     //パーツ破壊
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




