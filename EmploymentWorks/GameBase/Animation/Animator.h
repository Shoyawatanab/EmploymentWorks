/*
	１つのアニメーションに対してパーツの管理を行うクラス
*/
#pragma once
#include "GameBase/Actor.h"
#include <string>

class Transform;
class Animation2;

class Animator
{
public:

	//アニメーション名
	const  std::string& GetAnimaiionName() { return m_animationName; }
	//ループするかの取得　ture: ループする　false :ループなし
	bool GetIsLoop() const { return m_isLoop; }

public:
	//コンストラクタ
	Animator(Actor* owner
		,const std::string& animationName
		,const std::string& fimePath
		,std::vector<std::pair<std::string, Actor*>> actors);
	//デストラクタ
	~Animator();
	//更新処理　ture: 実行中　false :終了
	bool Update(const float& deltaTime);

	//アニメーションの再生
	void PlayAnimation();
	//再実行
	void Rerun();

private:

	//アニメーション情報の読み込み
	void LoadData(std::string finePath);

	//リセット
	void Reset();

private:
	//所有者
	Actor* m_ower;

	//アニメーション名
	std::string m_animationName;
	//ループ
	bool m_isLoop;
	//アニメーション全体の時間
	float m_animationTotalTime;
	//アニメーションスピード
	float m_speed;
	//パーツごとのデータ
	std::unordered_map<std::string,std::unique_ptr<Animation2>> m_partsData;
	//アニメーションの経過時間
	float m_animationTime;

};
