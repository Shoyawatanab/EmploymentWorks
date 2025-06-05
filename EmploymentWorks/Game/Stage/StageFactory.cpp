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
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
StageFactory::StageFactory(Scene* scene)
	:
	Actor(scene)
{
	//�X�e�[�W���̓ǂݍ���
	LoadStageData();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageFactory::~StageFactory()
{

}


/// <summary>
/// �X�e�[�W���̓ǂݍ���
/// </summary>
void StageFactory::LoadStageData()
{

	using namespace DirectX::SimpleMath;

	std::string number = "Stage";

	std::string fileaName = "Resources/Dates/Stages/" + number + ".json";

	std::ifstream file(fileaName.c_str());

	//�t�@�C�����J���Ȃ��Ƃ�
	if (!file.is_open())
	{
		throw std::runtime_error("json�t�@�C�����J���܂���");
	}

	//�t�@�C���̓��e��JSON�I�u�W�F�b�N�Ƃ��ăp�[�X
	nlohmann::json data = nlohmann::json::parse(file);


	//StageObject[](�s���N�F)���̃f�[�^��{}(�F)�̗v�f������
	for (const auto& item : data["StageObject"])
	{

		//�K�v�ϐ��̍쐬
		float boundingSphereRadius = 0;            //�~�̔���̔��a
		StageParameter stageParameter;

		//BoundingSphereRadius�����邩
		if (item.contains("BoundingSphereRadius"))
		{
			//BoundingSphereRadius�̗v�f�̒l����
			boundingSphereRadius = item["BoundingSphereRadius"];
		}


		//Position�����邩
		if (item.contains("Position"))
		{
			//Position�̗v�f����
			stageParameter.Position = DirectX::SimpleMath::Vector3(
				item["Position"]["x"],           //Position�̗v�f��x�̗v�f����x�l
				item["Position"]["y"],           //Position�̗v�f��x�̗v�f����y�l
				item["Position"]["z"]            //Position�̗v�f��x�̗v�f����z�l
			);
		}


		//Scale�����邩
		if (item.contains("Scale"))
		{
			//Scale�̗v�f����
			stageParameter.Scale = DirectX::SimpleMath::Vector3(
				item["Scale"]["x"],             //Scale�̗v�f��x�̗v�f����
				item["Scale"]["y"],             //Scale�̗v�f��y�̗v�f����
				item["Scale"]["z"]              //Scale�̗v�f��z�̗v�f����
			);
		}


		//Rotation�����邩
		if (item.contains("Rotation"))
		{
			//Rotation�̗v�f����
			stageParameter.Rotation = 
				MathUtil::ChangeVector3ToQuaternion(			
				DirectX::SimpleMath::Vector3(
				item["Rotation"]["x"],          //Rotation�̗v�f��x�̗v�f����
				item["Rotation"]["y"],          //Rotation�̗v�f��y�̗v�f����
				item["Rotation"]["z"]           //Rotation�̗v�f��z�̗v�f����
			));
		}

		//��ނɉ������I�u�W�F�N�g�̍쐬
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
