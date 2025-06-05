#include "pch.h"
#include "Animation2.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="animationName">アニメーション名</param>
/// <param name="actors">アニメーションさせたいオブジェクト</param>
Animation2::Animation2(Actor* owner, std::string animationName,std::string filePath ,std::vector<std::pair<std::string, Transform*>> actors)
	:
	m_ower{owner}
	,m_animationName{animationName}
	,m_actors{actors}
	,m_isLoop{false}
	,m_totalTime{}
{

	//アニメーションの読み込み　Jsonファイルから
	LoadData(filePath);

	//アニメーションデータを

}

/// <summary>
/// デストラクタ
/// </summary>
Animation2::~Animation2()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void Animation2::Update(const float& deltaTime)
{

	//パーツごとのアニメーションを更新する


	//トランスフォームの更新




}



/// <summary>
/// アニメーションの再生
/// </summary>
void Animation2::PlayAnimation()
{
}

/// <summary>
/// アニメーション情報の読み込み
/// </summary>
void Animation2::LoadData(std::string filePath)
{

	using json = nlohmann::json;

	std::ifstream file(filePath);

	//ファイルが開けないとき
	if (!file.is_open())
	{
		throw std::runtime_error("jsonファイルが開けません");
	}

	//ファイルの内容をJSONオブジェックとしてパース
	json data = json::parse(file);


	//アニメーションの種類
	std::string animationType = data["AnimationType"];

	//アニメーションのトータル時間
	float totalTime = data["AnimationTime"];

	//アニメーションのスピード
	float speed = data["AnimationSpeed"];

	//ループ再生かどうか
	bool isLoop = data["Loop"];

	//パーツごとにアニメーションを分けるための格納変数
	std::unordered_map<std::string, std::vector<AnimationKeyFram>> partsKeyFrame;



	//KeyFrame[](ピンク色)内のデータの{}(青色)の要素だけ回す
	for (const auto& frameData : data["KeyFrame"])
	{

		//フレームの時間の取得
		float frameTime = frameData["FreamTime"];



		//部位ごとの情報の取得
		for (const auto& partsData : frameData["Parts"])
		{
			std::string partsName = partsData["PartName"];

			AnimationKeyFram keyFrame;

			keyFrame.Time = frameTime;

			//Positionがあるか
			if (partsData.contains("Position"))
			{
				//Positionの要素を代入
				keyFrame.Position = DirectX::SimpleMath::Vector3(
					partsData["Position"]["x"],           //Positionの要素のxの要素を代入x値
					partsData["Position"]["y"],           //Positionの要素のxの要素を代入y値
					partsData["Position"]["z"]            //Positionの要素のxの要素を代入z値
				);
			}



			//Positionがあるか
			if (partsData.contains("Rotation"))
			{
				//Positionの要素を代入
				keyFrame.Rotation = DirectX::SimpleMath::Vector3(
					partsData["Rotation"]["x"],           //Positionの要素のxの要素を代入x値
					partsData["Rotation"]["y"],           //Positionの要素のxの要素を代入y値
					partsData["Rotation"]["z"]            //Positionの要素のxの要素を代入z値
				);
			}


			partsKeyFrame[partsName].push_back(keyFrame);

		}
	}

	//パーツごとのアニメーションを
	std::unordered_map<std::string, AnimationData> animations;

	for (auto& parts : partsKeyFrame)
	{

		std::string partsName = parts.first;

		std::vector<AnimationKeyFram> keyFrame = parts.second;

		animations[partsName].FramDatas = keyFrame;
		animations[partsName].TotalTime = totalTime;
		animations[partsName].Speed = speed;
		animations[partsName].IsLoop = isLoop;


	}



}
