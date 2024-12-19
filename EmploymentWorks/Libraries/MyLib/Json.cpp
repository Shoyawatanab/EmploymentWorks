#include "pch.h"
#include "Json.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

Json::Json()
{

}

Json::~Json()
{
}

//Jsonの読み込み
void Json::LoadJson()
{
}

std::vector<Json::StageData> Json::LoadStageDatas(const std::wstring& fileName)
{

	std::ifstream file(L"Resources/Dates/Stages/" + fileName + L".json");

	//ファイルが開けないとき
	if (!file.is_open())
	{
		throw std::runtime_error("jsonファイルが開けません");
	}

	//ファイルの内容をJSONオブジェックとしてパース
	json data = json::parse(file);

	//ステージ情報の保存配列を作成
	std::vector<StageData> stageData;

	//StageObject[](ピンク色)内のデータの{}(青色)の要素だけ回す
	for (const auto& item : data["StageObject"])
	{
		//ステージデータ変数
		StageData stage;
		//kindsの要素の値を代入
		stage.ModelName = item["kinds"];
		//BoundingSphereRadiusの要素の値を代入
		stage.BoundingSphereRadius = item["BoundingSphereRadius"];
		
		//Positionの要素を代入
		stage.Position = DirectX::SimpleMath::Vector3(
			item["Position"]["x"],           //Positionの要素のxの要素を代入x値
			item["Position"]["y"],           //Positionの要素のxの要素を代入y値
			item["Position"]["z"]            //Positionの要素のxの要素を代入z値
		);
		//Scaleの要素を代入
		stage.Scale = DirectX::SimpleMath::Vector3(
			item["Scale"]["x"],             //Scaleの要素のxの要素を代入
			item["Scale"]["y"],             //Scaleの要素のyの要素を代入
			item["Scale"]["z"]              //Scaleの要素のzの要素を代入
		);
		//Rotationの要素を代入
		stage.Rotation = DirectX::SimpleMath::Vector3(
			item["Rotation"]["x"],          //Rotationの要素のxの要素を代入
			item["Rotation"]["y"],          //Rotationの要素のyの要素を代入
			item["Rotation"]["z"]           //Rotationの要素のzの要素を代入
		);          
		
		//１つのステージデータを代入
		stageData.push_back(stage);

	}

	

	return stageData;

}
