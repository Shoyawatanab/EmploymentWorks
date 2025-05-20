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


/// <summary>
/// コンストラクタ
/// </summary>
WataLib::Animation::Animation()
	:
	m_animationData{}
	,m_currentAnimationData{}
	,m_position{}
	,m_rotation{}
	,m_time{}
	,m_normalAnimationType{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
WataLib::Animation::~Animation()
{



}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>ture:  アニメーション終了 false:　アニメーション中</returns>
bool WataLib::Animation::Update(const float& elapsedTime)
{
	//座標更新
	PositionUpdate(elapsedTime);
	//回転更新
	RotationUpdate(elapsedTime);

	//アニメーションが終わったら
	if (m_time > m_currentAnimationData.TotalTime)
	{
		//ループなら
		if (m_currentAnimationData.IsLoop)
		{
			//ループ
			m_time = 0;

		}
		//ループじゃないなら
		else
		{
			//再生アニメーションを通常アニメーションに変化
			InitializAnimationData(m_normalAnimationType);

		}

		//アニメーション終了
		return true;
	}

	m_time += elapsedTime;
	//アニメーション中
	return false;
}

/// <summary>
/// 座標の更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void WataLib::Animation::PositionUpdate(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;
	//初めの時間
	float startTime = m_fromToPosition.first.keyFrame.Time;
	//獣領事館
	float endTime = m_fromToPosition.second.keyFrame.Time;
	//割合
	float raito  = ( m_time - startTime ) / (endTime - startTime ) ;
	
	raito = std::min(raito, 1.0f);
	//座標を決める
	m_position = Vector3::SmoothStep(m_fromToPosition.first.keyFrame.Data, m_fromToPosition.second.keyFrame.Data, raito);

	//アニメーションの切り替え
	if (m_time >= endTime)
	{
		ChangePositionKeyFrame();
		
	}
	
}

/// <summary>
/// 回転の更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void WataLib::Animation::RotationUpdate(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;

	//初めの時間
	float startTime = m_fromToRotation.first.keyFrame.Time;
	//終わりの時間
	float endTime = m_fromToRotation.second.keyFrame.Time;
	//初めのデータ
	Vector3 startData = m_fromToRotation.first.keyFrame.Data;
	//終わりのデータ
	Vector3 endData = m_fromToRotation.second.keyFrame.Data;

	//割合
	float raito = 0;
	//０同時では計算をしないため
	if (endTime != startTime)
	{
		raito = (m_time - startTime) / (endTime - startTime);
	}



	raito = std::min(raito, 1.0f);
	
	//データから回転を作成
	Quaternion startRotation = Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(startData.y),
		DirectX::XMConvertToRadians(startData.x),
		DirectX::XMConvertToRadians(startData.z)
	);
	Quaternion endRotation = Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(endData.y),
		DirectX::XMConvertToRadians(endData.x),
		DirectX::XMConvertToRadians(endData.z)
	);

	//回転
	m_rotation = Quaternion::Slerp(startRotation, endRotation, raito);

	//アニメーションの切り替え
	if (m_time >= endTime)
	{
		ChangeRotationKeyFrame();

	}


}


/// <summary>
/// アニメーション
/// </summary>
/// <param name="animationType"></param>
/// <param name="data"></param>
/// <param name="isNormalAnimation"></param>
void WataLib::Animation::SetAnimationData(const std::string& animationType, const WataLib::Json::AnimationData& data, bool isNormalAnimation)
{
	

	auto it = m_animationData.find(animationType);

	//ある場合
	if (it != m_animationData.end())
	{
		return;
	}

// Position Rotationごとに分ける

	//Jsonからのフレームの情報
	std::vector<WataLib::Json::AnimationKeyFram> frameDatas = data.FramDatas;

	//アニメーション情報の保存変数
	AnimationData animationData;

	//必要情報を代入
	animationData.TypeName = animationType;
	animationData.TotalTime = data.TotalTime;
	animationData.Speed = data.Speed;
	animationData.IsLoop = data.IsLoop;


	//初めのフレームに値があるかどうか
	bool isStartFrame = false;
	//終わりのフレームに値があるかどうか
	bool isEndFrame = false;


	//フレームの情報の数だけループ
	for (auto& frameData : frameDatas)
	{

		//初めのデータがあるなら
		if (frameData.Time == 0.0f)
		{
			isStartFrame = true;
		}
		//終わりのデータがあるなら
		else if (frameData.Time == animationData.TotalTime)
		{
			isEndFrame = true;
		}

		//値がるなら
		if (frameData.Position != std::nullopt)
		{
			//一時的な値保存変数
			KeyFram frame;
			//フレーム時間の代入
			frame.Time = frameData.Time;
			//フレームの座標の代入
			frame.Data = frameData.Position.value();
			//後ろに代入
			animationData.Position.push_back(frame);

			//animationData.Position.insert(animationData.Position.end() - 1, frame);
		}
		//初め（0.0秒時）にデータがない場合
		else if (frameData.Time == 0.0f)
		{
			//一時的な値保存変数
			KeyFram frame;
			//フレーム時間の代入
			frame.Time = 0.0f;
			//フレームの回転の代入
			frame.Data = DirectX::SimpleMath::Vector3::Zero;
			//はじめのデータとして０初期化の代入
			animationData.Position.insert(animationData.Position.begin(), frame);

		}
		//アニメーションの終わり時にアニメーションのがない場合
		else if (frameData.Time == animationData.TotalTime)
		{
			
			//一時的な値保存変数
			KeyFram frame;
			//フレーム時間の代入
			frame.Time = animationData.TotalTime;
			//フレームの回転の代入
			frame.Data = DirectX::SimpleMath::Vector3::Zero;
			//終わりのデータとして０初期化の代入
			animationData.Position.push_back(frame);

		}


		//値があるなら
		if (frameData.Rotation != std::nullopt)
		{
			//一時的な値保存変数
			KeyFram frame;
			//フレーム時間の代入
			frame.Time = frameData.Time;
			//フレームの回転の代入
			frame.Data = frameData.Rotation.value();
			//後ろに代入
			animationData.Rotation.push_back(frame);
		}
		//初め（0.0秒時）にデータがない場合
		else if (frameData.Time == 0.0f)
		{
			//一時的な値保存変数
			KeyFram frame;
			//フレーム時間の代入
			frame.Time = 0.0f;
			//フレームの回転の代入
			frame.Data = DirectX::SimpleMath::Vector3::Zero;
			//はじめのデータとして０初期化の代入
			animationData.Rotation.insert(animationData.Rotation.begin(), frame);

		}
		//アニメーションの終わり時にアニメーションのがない場合
		else if (frameData.Time == animationData.TotalTime)
		{

			//一時的な値保存変数
			KeyFram frame;
			//フレーム時間の代入
			frame.Time = animationData.TotalTime;
			//フレームの回転の代入
			frame.Data = DirectX::SimpleMath::Vector3::Zero;
			//終わりのデータとして０初期化の代入
			animationData.Rotation.push_back(frame);

		}


	}

	//アニメーションの初めにデータがないなら
	if (!isStartFrame)
	{
		//一時的な値保存変数
		KeyFram frame;
		//フレーム時間の代入
		frame.Time = 0.0f;
		//フレームの回転の代入
		frame.Data = DirectX::SimpleMath::Vector3::Zero;
		//はじめのデータとして０初期化の代入
		animationData.Position.insert(animationData.Position.begin(), frame);
		animationData.Rotation.insert(animationData.Rotation.begin(), frame);


	}

	//アニメーションの終わりにデータがないなら
	if (!isEndFrame)
	{
		//一時的な値保存変数
		KeyFram frame;
		//フレーム時間の代入
		frame.Time = animationData.TotalTime;
		//フレームの回転の代入
		frame.Data = DirectX::SimpleMath::Vector3::Zero;
		//終わりのデータとして０初期化の代入
		animationData.Position.push_back(frame);
		animationData.Rotation.push_back(frame);

	}


	//座標　回転ごとに分けたデータと代入
	m_animationData[animationType] = animationData;


	//初期アニメーションの登録
	if (isNormalAnimation)
	{
		m_currentAnimationData = animationData;
		//通常アニメーションのtypeの登録
		m_normalAnimationType = animationType;
		//再生アニメーションの初期値
		InitializAnimationData(animationType);

	}

	

}


/// <summary>
/// アニメーションの切り替え
/// </summary>
/// <param name="animationType">経過時間</param>
void WataLib::Animation::ChangeAnimation(const std::string& animationType)
{

	auto it = m_animationData.find(animationType);

	if (it == m_animationData.end())
	{
		//ないならやらない
		return;
	}

	InitializAnimationData(animationType);

}

/// <summary>
/// アニメーションの初期化
/// </summary>
/// <param name="animationType"></param>
void WataLib::Animation::InitializAnimationData(const std::string& animationType)
{
	//再生アニメーション情報の変更
	//座標
	m_currentAnimationData = m_animationData[animationType];
	m_fromToPosition.first.keyFrame = m_currentAnimationData.Position[0];
	m_fromToPosition.first.Index = 0;
	m_fromToPosition.second.keyFrame = m_currentAnimationData.Position[1];
	m_fromToPosition.second.Index = 1;
	//回転
	m_fromToRotation.first.keyFrame = m_currentAnimationData.Rotation[0];
	m_fromToRotation.first.Index = 0;
	m_fromToRotation.second.keyFrame = m_currentAnimationData.Rotation[1];
	m_fromToRotation.second.Index = 1;

	m_time = 0;
}

/// <summary>
/// 座標のキーフレームの切り替え
/// </summary>
void WataLib::Animation::ChangePositionKeyFrame()
{

	m_fromToPosition.first = m_fromToPosition.second;

	int index = m_fromToPosition.second.Index;
	
	//Indexの範囲インクリメント　
	index++;
	//最大を超えたら０にする
	index = index % m_currentAnimationData.Position.size();

	m_fromToPosition.second.Index = index;
	m_fromToPosition.second.keyFrame = m_currentAnimationData.Position[index];
}

/// <summary>
/// 回転のキーフレームの切り替え
/// </summary>
void WataLib::Animation::ChangeRotationKeyFrame()
{
	m_fromToRotation.first = m_fromToRotation.second;

	int index = m_fromToRotation.second.Index;

	//Indexの範囲インクリメント　
	index++;
	//最大を超えたら０にする
	index = index % m_currentAnimationData.Rotation.size();

	m_fromToRotation.second.Index = index;
	m_fromToRotation.second.keyFrame = m_currentAnimationData.Rotation[index];

}

