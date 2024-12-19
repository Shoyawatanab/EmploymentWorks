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

//Json�̓ǂݍ���
void Json::LoadJson()
{
}

std::vector<Json::StageData> Json::LoadStageDatas(const std::wstring& fileName)
{

	std::ifstream file(L"Resources/Dates/Stages/" + fileName + L".json");

	//�t�@�C�����J���Ȃ��Ƃ�
	if (!file.is_open())
	{
		throw std::runtime_error("json�t�@�C�����J���܂���");
	}

	//�t�@�C���̓��e��JSON�I�u�W�F�b�N�Ƃ��ăp�[�X
	json data = json::parse(file);

	//�X�e�[�W���̕ۑ��z����쐬
	std::vector<StageData> stageData;

	//StageObject[](�s���N�F)���̃f�[�^��{}(�F)�̗v�f������
	for (const auto& item : data["StageObject"])
	{
		//�X�e�[�W�f�[�^�ϐ�
		StageData stage;
		//kinds�̗v�f�̒l����
		stage.ModelName = item["kinds"];
		//BoundingSphereRadius�̗v�f�̒l����
		stage.BoundingSphereRadius = item["BoundingSphereRadius"];
		
		//Position�̗v�f����
		stage.Position = DirectX::SimpleMath::Vector3(
			item["Position"]["x"],           //Position�̗v�f��x�̗v�f����x�l
			item["Position"]["y"],           //Position�̗v�f��x�̗v�f����y�l
			item["Position"]["z"]            //Position�̗v�f��x�̗v�f����z�l
		);
		//Scale�̗v�f����
		stage.Scale = DirectX::SimpleMath::Vector3(
			item["Scale"]["x"],             //Scale�̗v�f��x�̗v�f����
			item["Scale"]["y"],             //Scale�̗v�f��y�̗v�f����
			item["Scale"]["z"]              //Scale�̗v�f��z�̗v�f����
		);
		//Rotation�̗v�f����
		stage.Rotation = DirectX::SimpleMath::Vector3(
			item["Rotation"]["x"],          //Rotation�̗v�f��x�̗v�f����
			item["Rotation"]["y"],          //Rotation�̗v�f��y�̗v�f����
			item["Rotation"]["z"]           //Rotation�̗v�f��z�̗v�f����
		);          
		
		//�P�̃X�e�[�W�f�[�^����
		stageData.push_back(stage);

	}

	

	return stageData;

}
