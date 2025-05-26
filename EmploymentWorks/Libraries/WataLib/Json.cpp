#include "pch.h"
#include "Json.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

/// <summary>
/// �R���X�g���N�^
/// </summary>
WataLib::Json::Json()
	:
	m_stageParamter{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WataLib::Json::~Json()
{
}


/// <summary>
/// �X�e�[�W�f�[�^�̓ǂݍ���
/// </summary>
/// <param name="fileName">�t�@�C����</param>
/// <returns>�X�e�[�W�f�[�^</returns>
WataLib::Json::StageData WataLib::Json::LoadStageDatas(const std::wstring& fileName)
{

	std::ifstream file(L"Resources/Dates/Stages/" + fileName + L".json");

	//�t�@�C�����J���Ȃ��Ƃ�
	if (!file.is_open())
	{
		throw std::runtime_error("json�t�@�C�����J���܂���");
	}

	//�t�@�C���̓��e��JSON�I�u�W�F�b�N�Ƃ��ăp�[�X
	json data = json::parse(file);

	StageData stageData;

	//�K�v�f�[�^�̎擾

	stageData.BoomerangCount = data["BoomerangCount"];



	//�X�e�[�W���̕ۑ��z����쐬
	std::vector<ObjectData> objectData;

	//StageObject[](�s���N�F)���̃f�[�^��{}(�F)�̗v�f������
	for (const auto& item : data["StageObject"])
	{
		//�X�e�[�W�f�[�^�ϐ�
		ObjectData object;
		//kinds�̗v�f�̒l����
		object.ModelName = item["kinds"];


		//BoundingSphereRadius�����邩
		if (item.contains("BoundingSphereRadius"))
		{
			//BoundingSphereRadius�̗v�f�̒l����
			object.BoundingSphereRadius = item["BoundingSphereRadius"];
		}
		//�Ȃ����
		else
		{
			object.BoundingSphereRadius = 0.0f;
		}

		//Position�����邩
		if (item.contains("Position"))
		{
			//Position�̗v�f����
			object.Position = DirectX::SimpleMath::Vector3(
				item["Position"]["x"],           //Position�̗v�f��x�̗v�f����x�l
				item["Position"]["y"],           //Position�̗v�f��x�̗v�f����y�l
				item["Position"]["z"]            //Position�̗v�f��x�̗v�f����z�l
			);
		}
		//�Ȃ����
		else
		{
			object.Position = DirectX::SimpleMath::Vector3::Zero;
		}

		//Scale�����邩
		if (item.contains("Scale"))
		{
			//Scale�̗v�f����
			object.Scale = DirectX::SimpleMath::Vector3(
				item["Scale"]["x"],             //Scale�̗v�f��x�̗v�f����
				item["Scale"]["y"],             //Scale�̗v�f��y�̗v�f����
				item["Scale"]["z"]              //Scale�̗v�f��z�̗v�f����
			);
		}
		//�Ȃ����
		else
		{
			object.Scale = DirectX::SimpleMath::Vector3::Zero;
		}

		//Rotation�����邩
		if (item.contains("Rotation"))
		{
			//Rotation�̗v�f����
			object.Rotation = DirectX::SimpleMath::Vector3(
				item["Rotation"]["x"],          //Rotation�̗v�f��x�̗v�f����
				item["Rotation"]["y"],          //Rotation�̗v�f��y�̗v�f����
				item["Rotation"]["z"]           //Rotation�̗v�f��z�̗v�f����
			);
		}
		//�Ȃ����
		else
		{
			object.Rotation = DirectX::SimpleMath::Vector3::Zero;
		}

		
		//�P�̃X�e�[�W�f�[�^����
		objectData.push_back(object);

	}


	//�I�u�W�F�N�g�f�[�^�̓o�^
	stageData.ObjectDatas = objectData;


	return stageData;

}

/// <summary>
/// �A�j���[�V�����f�[�^�̓ǂݍ���
/// </summary>
/// <param name="fileName">�t�@�C����</param>
/// <returns>�A�j���[�V�����f�[�^</returns>
std::unordered_map<std::string, WataLib::Json::AnimationData> WataLib::Json::LoadAnimationData(const std::wstring& fileName)
{
	std::ifstream file(L"Resources/Dates/Animation/" + fileName + L".json");

	//�t�@�C�����J���Ȃ��Ƃ�
	if (!file.is_open())
	{
		throw std::runtime_error("json�t�@�C�����J���܂���");
	}

	//�t�@�C���̓��e��JSON�I�u�W�F�b�N�Ƃ��ăp�[�X
	json data = json::parse(file);


	//�A�j���[�V�����̎��
	std::string animationType = data["AnimationType"];

	//�A�j���[�V�����̃g�[�^������
	float totalTime = data["AnimationTime"];

	//�A�j���[�V�����̃X�s�[�h
	float speed = data["AnimationSpeed"];

	//���[�v�Đ����ǂ���
	bool isLoop = data["Loop"];

	//�p�[�c���ƂɃA�j���[�V�����𕪂��邽�߂̊i�[�ϐ�
	std::unordered_map<std::string, std::vector<AnimationKeyFram>> partsKeyFrame;

	

	//KeyFrame[](�s���N�F)���̃f�[�^��{}(�F)�̗v�f������
	for (const auto& frameData : data["KeyFrame"])
	{
		
		//�t���[���̎��Ԃ̎擾
		float frameTime = frameData["FreamTime"];



		//���ʂ��Ƃ̏��̎擾
		for (const auto& partsData : frameData["Parts"])
		{
			std::string partsName = partsData["PartName"];

			AnimationKeyFram keyFrame;

			keyFrame.Time = frameTime;

			//Position�����邩
			if (partsData.contains("Position"))
			{
				//Position�̗v�f����
				keyFrame.Position = DirectX::SimpleMath::Vector3(
					partsData["Position"]["x"],           //Position�̗v�f��x�̗v�f����x�l
					partsData["Position"]["y"],           //Position�̗v�f��x�̗v�f����y�l
					partsData["Position"]["z"]            //Position�̗v�f��x�̗v�f����z�l
				);
			}



			//Position�����邩
			if (partsData.contains("Rotation"))
			{
				//Position�̗v�f����
				keyFrame.Rotation = DirectX::SimpleMath::Vector3(
					partsData["Rotation"]["x"],           //Position�̗v�f��x�̗v�f����x�l
					partsData["Rotation"]["y"],           //Position�̗v�f��x�̗v�f����y�l
					partsData["Rotation"]["z"]            //Position�̗v�f��x�̗v�f����z�l
				);
			}


			partsKeyFrame[partsName].push_back(keyFrame);
			
		}
	}

	//�p�[�c���Ƃ̃A�j���[�V������
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

	return animations;
}
