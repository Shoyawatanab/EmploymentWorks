#pragma once
#include <variant>


//状態・・状態遷移などに使用
//活動・・どんなことがをしたか　起こったか

//ゲームの種類
enum class MessageType : int
{
	NONE = -1
	//シーン切り替え
	,CHANGE_TITLE_SCENE                           //tタイトルシーンに切り替え
	,CHANGE_SELECT_SCENE						  //セレクトシーンに切り替え
	,CHANGE_PLAY_SCENE							  //プレイシーンに切り替え


	//ゲームの活動
	,GAME_CLEAR                                    //ゲームクリア
	,GAME_OVER									   //ゲームオーバー
	,ENEMY_DAMAGE                                  //敵のダメージ

	//ゲームの状態



	//プレイヤの活動
	,PLAYER_GET_REDAY                              //プレイヤの構えの活動
	,PLAYER_GET_REDAY_END                          //プレイヤの構え終了の活動

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


	//鳥敵の活動



	//鳥敵の状態
	,BIRD_IDLE_STATE                              //鳥敵の通常状態
	,BIRD_MOVE_STATE							  //鳥敵の動き状態
	,BIRD_BEAM_ATTACK_STATE						  //鳥敵のビーム攻撃状態

	//鳥敵の弾の活動



	//鳥敵の弾の状態
	, BIRD_BULLET_IDLE_STATE                              //鳥敵の弾の通常状態
	, BIRD_BULLET_CHAGE_STATE							  //鳥敵の弾のチャージ状態
	, BIRD_BULLET_SHOT_STATE						      //鳥敵の弾のショット状態

};





/*
	名前　　　　　　　　　　　　　　　　　　追加データ (型名・用途,型名・用途　・・・・)
	BOOMERANG_IDEL_STATE 　　　　　　　　　Boomerang  どのブーメランのステートを切り替えるのか

	BOSS_DAMAGE　　　　　　　　　　　　　　float  残りHP割合　
	
*/













