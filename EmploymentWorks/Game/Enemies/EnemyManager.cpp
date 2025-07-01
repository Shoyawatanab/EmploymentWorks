#include "pch.h"
#include "EnemyManager.h"
#include "Game/Enemies/Enemys.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/GlobalGameData.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Messenger/Global/GlobalMessages.h"
#include "Game/Fade/FadeManager.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="player">�v���C��</param>
EnemyManager::EnemyManager(Scene* scene,Player* player)
	:
	Actor(scene)
	,m_player{player}
{
	using namespace DirectX::SimpleMath;

	//�X�e�[�W�f�[�^�̓ǂݍ���
	LoadData();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyManager::~EnemyManager()
{
}

/// <summary>
/// �G�̎��S
/// </summary>
/// <param name="enemy"></param>
void EnemyManager::DeathEnemy(Actor* actor)
{
	//�T��
	auto enemy = std::find(m_enemys.begin(), m_enemys.end(), actor);
	
	//�����
	if (enemy != m_enemys.end())
	{
		//�폜
		m_enemys.erase(enemy);
	}



	//���ׂĂ̓G��|������
	if (m_enemys.empty())
	{
		//���U���g�V�[���ɕύX�̒ʒm
		GlobalMessenger::GetInstance()->Notify(GlobalMessageType::CHANGE_RESULT_SCENE);

		FadeManager::GetInstance()->StartFadeIn();

	}



}


/// <summary>
/// �X�e�[�W�f�[�^�̓ǂݍ���
/// </summary>
void EnemyManager::LoadData()
{

	using namespace DirectX::SimpleMath;

	using json = nlohmann::json;


	//�X�e�[�W�ԍ��̎擾
	int stageNumber = GlobalGameData::GetInstance()->GetSelectStateNumber();


	std::ifstream file(L"Resources/Json/Stage/Stage" + std::to_wstring(stageNumber) + L"/Enemy.json");

	//�t�@�C�����J���Ȃ��Ƃ�
	if (!file.is_open())
	{
		throw std::runtime_error("json�t�@�C�����J���܂���");
	}

	//�t�@�C���̓��e��JSON�I�u�W�F�b�N�Ƃ��ăp�[�X
	json data = json::parse(file);

	//StageObject[](�s���N�F)���̃f�[�^��{}(�F)�̗v�f������
	for (const auto& item : data["StageObject"])
	{

		//kinds�̗v�f�̒l����
		std::string kinds = item["kinds"];

		if (kinds == "BossEnemy")
		{
			int a = 0;
		}

		//Position�̗v�f����
		Vector3 position;

		//Position�����邩
		if (item.contains("Position"))
		{
			//Position�̗v�f����
			position = Vector3(
				item["Position"]["x"],           //Position�̗v�f��x�̗v�f����x�l
				item["Position"]["y"],           //Position�̗v�f��x�̗v�f����y�l
				item["Position"]["z"]            //Position�̗v�f��x�̗v�f����z�l
			);
		}
		//�Ȃ����
		else
		{
			position = DirectX::SimpleMath::Vector3::Zero;
		}

		Vector3 scale;

		//Scale�����邩
		if (item.contains("Scale"))
		{
			//Scale�̗v�f����
			scale = Vector3(
				item["Scale"]["x"],             //Scale�̗v�f��x�̗v�f����
				item["Scale"]["y"],             //Scale�̗v�f��y�̗v�f����
				item["Scale"]["z"]              //Scale�̗v�f��z�̗v�f����
			);
		}
		//�Ȃ����
		else
		{
			scale = Vector3::Zero;
		}

		Quaternion rotation;

		//Rotation�����邩
		if (item.contains("Rotation"))
		{
			//Rotation�̗v�f����
			rotation = Quaternion::CreateFromYawPitchRoll(
				item["Rotation"]["y"],          
				item["Rotation"]["x"],          
				item["Rotation"]["z"]           
			);
		}
		//�Ȃ����
		else
		{
			rotation = Quaternion::Identity;
		}



		if (kinds == "BossEnemy")
		{
			//�{�X�G�̍쐬
			auto boss = GetScene()->AddActor<BossEnemy>(GetScene(),  scale, position, rotation, m_player);
			boss->SetEnemyManager(this);
			m_enemys.push_back(boss);


		}
		else if (kinds == "BirdEnemy")
		{
			//���G�̍쐬
			auto bird = GetScene()->AddActor<BirdEnemy>(GetScene(), scale, position, rotation, m_player);
			bird->SetEnemyManager(this);
			m_enemys.push_back(bird);


		}


	}



}
