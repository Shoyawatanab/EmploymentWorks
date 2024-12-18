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

std::vector<Json::StageParamater> Json::LoadStageParameter(const std::wstring& fileName)
{

	std::ifstream file(L"Resources/Dates/Stages/" + fileName + L".json");

	//ファイルが開けないとき
	if (!file.is_open())
	{
		throw std::runtime_error("jsonファイルが開けません");
	}

	//ファイルの内容をJSONオブジェックとしてパース
	json data = json::parse(file);

	std::vector<StageParamater> stagePramater;

	//"StageObject"nのデータを処理
	for (const auto& item : data["StageObject"])
	{

		StageParamater stage;

		stage.ModelName = item["kinds"];
		stage.BoundingSphereRadius = item["BoundingSphereRadius"];
		
		stage.Position = DirectX::SimpleMath::Vector3(
			item["Position"]["x"],
			item["Position"]["y"],
			item["Position"]["z"]
		);
		stage.Scale = DirectX::SimpleMath::Vector3(
			item["Scale"]["x"],
			item["Scale"]["y"],
			item["Scale"]["z"]
		);
		stage.Rotation = DirectX::SimpleMath::Vector3(
			item["Rotation"]["x"],
			item["Rotation"]["y"],
			item["Rotation"]["z"]
		);
		
		stagePramater.push_back(stage);

	}

	

	return stagePramater;

}
