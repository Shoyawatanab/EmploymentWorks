/*
	@file	CSV.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "Animation.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

Animation::Animation()
	:
	m_animation{}
	,m_playBackType{}
	,m_totalTime{}
	,m_keyFrameIndex{}
	,m_state{AnimationState::None}
{
}

Animation::~Animation()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns> Animation情報　Timeは経過時間 </returns>
Animation::AnimationState Animation::Update(float elapsdTime)
{
	

	if (m_animation.empty() || m_state == AnimationState::End)
	{	
		return m_state;
	}

	m_state = Animation::AnimationState::Running;

	//時間の割合を求める
	float ratio = m_totalTime / m_animation[m_keyFrameIndex + 1].Time;
	//割合が１を超えないようにする
	ratio = std::min(ratio, 1.0f);
	//Lerp関数で回転を更新
	m_animationRotate = Quaternion::Lerp(m_animation[m_keyFrameIndex].Rotation, m_animation[m_keyFrameIndex + 1].Rotation, ratio);
	
	//時間の加算
	m_totalTime += elapsdTime;

	//区切りが終わったら
	if (ratio >= 1)
	{
		//時間の初期化
		m_totalTime = 0;
		//次のアニメーションに行くために
		m_keyFrameIndex++;

		//最後まで行ったら
		if (m_keyFrameIndex >= m_animation.size() -1)
		{
			switch (m_playBackType)
			{
				case Animation::Loop:
					//初めに戻す
					m_keyFrameIndex = 0;
					break;
				case Animation::Once:
					//終了にする
					m_state = AnimationState::End;
					break;
				default:
					break;
			}
			m_keyFrameIndex = 0;
		}

	}




	return m_state;
}

/// <summary>
/// アニメーションの登録
/// </summary>
/// <param name="animations">アニメーション情報</param>
/// <param name="PlayBackType">再生の種類</param>
void Animation::SetAnimation(std::vector<AnimationKeyFrame> animations, AnimationPlayBackType PlayBackType)
{

	m_animation = animations;

	m_playBackType = PlayBackType;

}

void Animation::ResetAnimation()
{

	m_keyFrameIndex = 0;
	m_totalTime = 0;
	m_state = AnimationState::None;

}
