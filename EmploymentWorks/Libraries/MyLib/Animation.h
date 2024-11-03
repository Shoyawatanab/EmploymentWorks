#pragma once
#include <unordered_map>




class Animation final 
{
public:

	enum AnimationState
	{
		None,
		Running,   //実行中
		End        //終了

	};

	//アニメーションの再生種類
	enum AnimationPlayBackType
	{
		Loop,   //ループ
		Once,   //一回だけ
	}; 

	struct AnimationKeyFrame
	{
		//DirectX::SimpleMath::Vector3 Scale;        //大きさ
		//DirectX::SimpleMath::Vector3 Position;      //座標
		DirectX::SimpleMath::Quaternion Rotation;   //回転　
		float Time;                                 //発生する時間
	};

public:

	Animation();
	~Animation();

	AnimationState Update(float elapsdTime);

public:

	void SetAnimation(std::vector<AnimationKeyFrame> animations, AnimationPlayBackType PlayBackType);
	//アニメーションの回転の取得
	DirectX::SimpleMath::Quaternion GetAnimationRotate() { return m_animationRotate; }

	void ResetAnimation();
private:

	
	//アニメーションの再生種類
	AnimationPlayBackType m_playBackType;
	//アニメーション
	std::vector<AnimationKeyFrame> m_animation;
	//トータル時間
	float m_totalTime;
	//実行中にアニメーションのインデックス
	int m_keyFrameIndex;
	//実行中アニメーションの回転
	DirectX::SimpleMath::Quaternion m_animationRotate;
	//アニメーションの状態
	AnimationState m_state;
};
