#include "pch.h"
#include "Animation2.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="animationName">�A�j���[�V������</param>
/// <param name="actors">�A�j���[�V�������������I�u�W�F�N�g</param>
Animation2::Animation2(Actor* owner, std::string animationName,std::string filePath ,std::vector<std::pair<std::string, Transform*>> actors)
	:
	m_ower{owner}
	,m_animationName{animationName}
	,m_actors{actors}
	,m_isLoop{false}
	,m_totalTime{}
{

	//�A�j���[�V�����̓ǂݍ��݁@Json�t�@�C������
	LoadData(filePath);

	//�A�j���[�V�����f�[�^��

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Animation2::~Animation2()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void Animation2::Update(const float& deltaTime)
{

	//�p�[�c���Ƃ̃A�j���[�V�������X�V����


	//�g�����X�t�H�[���̍X�V




}



/// <summary>
/// �A�j���[�V�����̍Đ�
/// </summary>
void Animation2::PlayAnimation()
{
}

/// <summary>
/// �A�j���[�V�������̓ǂݍ���
/// </summary>
void Animation2::LoadData(std::string filePath)
{

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



}
