#include "pch.h"
#include "Animator.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "GameBase/Component/Components.h"
#include "GameBase/Animation/Animation.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="animationName">�A�j���[�V������</param>
/// <param name="actors">�A�j���[�V�������������I�u�W�F�N�g</param>
Animator::Animator(Actor* owner
	, const std::string& animationName
	, const std::string& filePath
	, std::vector<std::pair<std::string, Actor*>> actors)
	:
	m_ower{owner}
	,m_animationName{animationName}
	,m_isLoop{false}
	, m_animationTotalTime{}
	,m_partsData{}
	, m_animationTime{}
	,m_isEnd{false}
{

	//Animation�̍쐬
	for (auto& [name, actor] : actors) 
	{
		m_partsData[name] = std::make_unique<Animation>(actor);
	}

	//�A�j���[�V�����̓ǂݍ��݁@Json�t�@�C������
	LoadData(filePath);

	//�f�[�^�̕��ёւ�
	for (auto& parts : m_partsData)
	{
		parts.second->DataSort();
	}

}



/// <summary>
/// �f�X�g���N�^
/// </summary>
Animator::~Animator()
{
	m_partsData.clear();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
/// <returns>ture: ���s���@false :�I��</returns>
bool Animator::Update(const float& deltaTime)
{

	//�p�[�c���Ƃ̃A�j���[�V�������X�V
	for (auto& parts : m_partsData)
	{
		//�A�j���[�V�����̍X�V
		parts.second->Update(m_animationTime);

	}
	
	//���Ԃ̉��Z
	m_animationTime += deltaTime;
	
	//�A�j���[�V��������ʂ�I�������
	if (m_animationTime >= m_animationTotalTime)
	{ 
		m_isEnd = true;
		//�A�j���[�V�����I��
		return true;
	}
	
	//�A�j���[�V������
	return false;
}



/// <summary>
/// �A�j���[�V�����̍Đ�
/// </summary>
void Animator::PlayAnimation()
{
}

/// <summary>
/// �Ď��s
/// </summary>
void Animator::Rerun()
{
	//�o�ߎ��Ԃ̃��Z�b�g
	m_animationTime = 0.0f;
	m_isEnd = false;

	for (auto& parts : m_partsData)
	{
		//Animation�̃��Z�b�g
		parts.second->Reset();
	}
}

/// <summary>
/// �A�j���[�V�������̓ǂݍ���
/// </summary>

/// <param name="filePath">�t�@�C���p�X</param>
void Animator::LoadData(std::string filePath)
{
	using namespace DirectX::SimpleMath;
	using json = nlohmann::json;

	std::ifstream file(filePath);

	//�t�@�C�����J���Ȃ��Ƃ�
	if (!file.is_open())
	{
		throw std::runtime_error("json�t�@�C�����J���܂���");
	}

	//�t�@�C���̓��e��JSON�I�u�W�F�b�N�Ƃ��ăp�[�X
	json data = json::parse(file);


	//�A�j���[�V�����̎��

	//�A�j���[�V�����̃g�[�^������
	m_animationTotalTime = data["AnimationTime"];

	//�A�j���[�V�����̃X�s�[�h
	m_speed = data["AnimationSpeed"];

	//���[�v�Đ����ǂ���
	m_isLoop = data["Loop"];

	//�A�j���[�V�������Ԃ̃Z�b�g
	for (auto& parts : m_partsData)
	{
		parts.second->SetAnimationTotalTime(m_animationTotalTime);
	}


	//KeyFrame[](�s���N�F)���̃f�[�^��{}(�F)�̗v�f������
	for (const auto& frameData : data["KeyFrame"])
	{

		//�t���[���̎��Ԃ̎擾
		float frameTime = frameData["FreamTime"];


		//���ʂ��Ƃ̏��̎擾
		for (const auto& partsData : frameData["Parts"])
		{
			std::string partsName = partsData["PartName"];

			//�p�[�c�f�[�^�ɓ������O�����邩
			auto it = m_partsData.find(partsName);

			//�Ȃ���Ύ���
			if (it == m_partsData.end())
			{
				continue;
			}


			//Position�����邩
			if (partsData.contains("Position"))
			{
				 Vector3 position= DirectX::SimpleMath::Vector3(
					partsData["Position"]["x"],           //Position�̗v�f��x�̗v�f����x�l
					partsData["Position"]["y"],           //Position�̗v�f��x�̗v�f����y�l
					partsData["Position"]["z"]            //Position�̗v�f��x�̗v�f����z�l
				);
				//Position�ƃt���[�����Ԃ̑��
				it->second->AddPositionData(frameTime,position);

			}



			//Rotation�����邩
			if (partsData.contains("Rotation"))
			{
				//Position�̗v�f����
				Vector3 rotation = DirectX::SimpleMath::Vector3(
					partsData["Rotation"]["x"],           //Position�̗v�f��x�̗v�f����x�l
					partsData["Rotation"]["y"],           //Position�̗v�f��x�̗v�f����y�l
					partsData["Rotation"]["z"]            //Position�̗v�f��x�̗v�f����z�l
				);
	
				//Rotation�ƃt���[�����Ԃ̑��
				it->second->AddRotateData(frameTime, rotation);

			}
						
		}
	}

}






