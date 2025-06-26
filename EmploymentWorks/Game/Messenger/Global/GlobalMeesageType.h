#pragma once
//状態・・状態遷移などに使用
//活動・・どんなことがをしたか　起こったか

//ゲームの種類
enum class GlobalMessageType : int
{
	NONE = -1
	//シーン切り替え
	, CHANGE_TITLE_SCENE                           //tタイトルシーンに切り替え
	, CHANGE_SELECT_SCENE						  //セレクトシーンに切り替え
	, CHANGE_PLAY_SCENE							  //プレイシーンに切り替え


};





/*
	名前　　　　　　　　　　　　　　　　　　追加データ (型名・用途,型名・用途　・・・・)
	BOOMERANG_IDEL_STATE 　　　　　　　　　Boomerang  どのブーメランのステートを切り替えるのか

	BOSS_DAMAGE　　　　　　　　　　　　　　float  残りHP割合　

*/



