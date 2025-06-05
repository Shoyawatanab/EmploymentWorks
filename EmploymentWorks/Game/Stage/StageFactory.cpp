#include "pch.h"
#include "StageFactory.h"

#include <fstream>
#include <sstream>
#include <string>

#include "nlohmann/json.hpp"
#include "Game/Stage/StageObjects.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/MathUtil.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
StageFactory::StageFactory(Scene* scene)
	:
	Actor(scene)
{
	//ステージ情報の読み込み
	LoadStageData();
}

/// <summary>
/// デストラクタ
/// </summary>
StageFactory::~StageFactory()
{

}


/// <summary>
/// ステージ情報の読み込み
/// </summary>
void StageFactory::LoadStageData()
{

	using namespace DirectX::SimpleMath;

	std::string number = "Stage";

	std::string fileaName = "Resources/Dates/Stages/" + number + ".json";

	std::ifstream file(fileaName.c_str());

	//ファイルが開けないとき
	if (!file.is_open())
	{
		throw std::runtime_error("jsonファイルが開けません");
	}

	//ファイルの内容をJSONオブジェックとしてパース
	nlohmann::json data = nlohmann::json::parse(file);


	//StageObject[](ピンク色)内のデータの{}(青色)の要素だけ回す
	for (const auto& item : data["StageObject"])
	{

		//必要変数の作成
		float boundingSphereRadius = 0;            //円の判定の半径
		StageParameter stageParameter;

		//BoundingSphereRadiusがあるか
		if (item.contains("BoundingSphereRadius"))
		{
			//BoundingSphereRadiusの要素の値を代入
			boundingSphereRadius = item["BoundingSphereRadius"];
		}


		//Positionがあるか
		if (item.contains("Position"))
		{
			//Positionの要素を代入
			stageParameter.Position = DirectX::SimpleMath::Vector3(
				item["Position"]["x"],           //Positionの要素のxの要素を代入x値
				item["Position"]["y"],           //Positionの要素のxの要素を代入y値
				item["Position"]["z"]            //Positionの要素のxの要素を代入z値
			);
		}


		//Scaleがあるか
		if (item.contains("Scale"))
		{
			//Scaleの要素を代入
			stageParameter.Scale = DirectX::SimpleMath::Vector3(
				item["Scale"]["x"],             //Scaleの要素のxの要素を代入
				item["Scale"]["y"],             //Scaleの要素のyの要素を代入
				item["Scale"]["z"]              //Scaleの要素のzの要素を代入
			);
		}


		//Rotationがあるか
		if (item.contains("Rotation"))
		{
			//Rotationの要素を代入
			stageParameter.Rotation = 
				MathUtil::ChangeVector3ToQuaternion(			
				DirectX::SimpleMath::Vector3(
				item["Rotation"]["x"],          //Rotationの要素のxの要素を代入
				item["Rotation"]["y"],          //Rotationの要素のyの要素を代入
				item["Rotation"]["z"]           //Rotationの要素のzの要素を代入
			));
		}

		//種類に応じたオブジェクトの作成
		if (item["kinds"] == "Wall")
		{
			auto wall = GetScene()->AddActor<Wall>(GetScene(), stageParameter);

			
		}
		else if (item["kinds"] == "Floor")
		{
			auto wall = GetScene()->AddActor<Floor>(GetScene(), stageParameter);

		}
	}




}
