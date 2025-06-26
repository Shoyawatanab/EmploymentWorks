#pragma once


//状態・・状態遷移などに使用
//活動・・どんなことがをしたか　起こったか

//ゲームの種類
enum class SceneMessageType : int
{
	NONE = -1

	//ゲームの活動
	,GAME_CLEAR                                    //ゲームクリア
	,GAME_OVER									   //ゲームオーバー
	,ENEMY_DAMAGE                                  //敵のダメージ

	//ゲームの状態



	//プレイヤの活動
	,PLAYER_GET_REDAY                              //プレイヤの構えの活動
	,PLAYER_GET_REDAY_END                          //プレイヤの構え終了の活動
	,PLAYER_DAMAGE                                 //プレイヤのダメージ

	//プレイヤの状態
	,PLAYER_IDLE_STATE                             //プレイヤの通常状態
	,PLAYER_BOOMERANG_ATTACK_STATE                 //プレイヤのブーメラン攻撃状態
	,PLAYER_BOOMERANG_GET_READY_STATE              //プレイヤのブーメランの構え状態

	//ブーメランの活動
	, BOOMERANG_GET_READY                          //ブーメランを構える活動
	, BOOMERANG_THROW                              //ブーメランを投げる活動
	, BOOMERANG_THROW_STOP                         //ブーメランを投げるのをやめる活動
	, BOOMERANG_CATCH                             //ブーメランをキャッチする活動


	//ブーメランの状態
	,BOOMERANG_IDEL_STATE                         //ブーメランの通常状態
	,BOOMERANG_GET_READY_STATE                    //ブーメランの構え状態
	,BOOMERANG_THROW_STATE                        //ブーメランの投げ状態

	//ボス敵の活動
	,BOSS_DAMAGE                                 //ボスがダメージを受けた活動
	,BOSS_DEFEATED                               //ボスを倒した活動

	//ボステキの状態
	,BOSS_IDLE_STATE                              //ボス敵の通常状態
	,BOSS_BEAM_ATTACK_STATE                       //ボス敵のビーム攻撃状態
	,BOSS_JUMP_ATTACK_STATE                       //ボス敵のジャンプ攻撃状態
	,BOSS_WAKING_STATE	                          //ボス敵の歩き状態
	,BOSS_SWING_DOWN_STATE	                      //ボス敵の振り下ろし攻撃状態

};





/*
	名前　　　　　　　　　　　　　　　　　　追加データ (型名・用途,型名・用途　・・・・)
	BOOMERANG_IDEL_STATE 　　　　　　　　　Boomerang  どのブーメランのステートを切り替えるのか

	BOSS_DAMAGE　　　　　　　　　　　　　　float  残りHP割合　
	
*/













