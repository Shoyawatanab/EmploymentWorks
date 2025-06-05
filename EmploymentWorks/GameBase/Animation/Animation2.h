#pragma once
#include "GameBase/Actor.h"
#include <string>
#include <optional>


class Animation2
{
public:

	//アニメーションのJson読み込み専用構造体

	struct AnimationKeyFram
	{
		float Time;                                //経過時間
		std::optional<DirectX::SimpleMath::Vector3>  Scale;
		std::optional< DirectX::SimpleMath::Vector3> Position;	    //経過時間に対しての座標
		std::optional< DirectX::SimpleMath::Vector3> Rotation; 		//経過時間に対しての回転

	};

	struct AnimationData
	{
		float TotalTime;                              //アニメーション全体の時間
		float Speed;								  //アニメーションの進行スピード
		bool IsLoop;								  //1アニメーションをループさせるか
		std::vector<AnimationKeyFram> FramDatas;	  //キーフレームの情報　時間順に並んでいるものとする

	};

public:

	//アニメーション名
	std::string GetAnimaiionName() { return m_animationName; }

public:
	//コンストラクタ
	Animation2(Actor* owner,std::string animationName, std::string fimePath,std::vector<std::pair<std::string, Transform*>> actors);
	//デストラクタ
	~Animation2();

	void Update(const float& deltaTime);

	//アニメーションの再生
	void PlayAnimation();

private:

	//アニメーション情報の読み込み
	void LoadData(std::string finePath);

private:
	//所有者
	Actor* m_ower;

	//アニメーション名
	std::string m_animationName;

	//アニメーション指せるオブジェクト
	std::vector<std::pair<std::string ,Transform*>> m_actors;
	//ループ
	bool m_isLoop;
	//
	float m_totalTime;
	//
	float m_speed;


};
