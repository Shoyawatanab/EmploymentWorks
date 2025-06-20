/*
	@file	CSV.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "CSV.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

#include <fstream>
#include <string>
#include <sstream>


/// <summary>
/// �u�[��������csv�t�@�C���̓ǂݍ���
/// </summary>
/// <returns></returns>
std::vector<DirectX::SimpleMath::Vector3> WataLib::CSV::LoadCSVBoomerang()
{
	std::string line;  //1�s
	//�t�@�C���̃I�[�v��
	std::ifstream fin(L"Resources/Dates/Boomerang.csv");
	//�I�[�I�E���ł�����
	if (!fin.is_open())
	{
		//�G���[�Ȃ�
		return {};
	}

	std::vector<DirectX::SimpleMath::Vector3> Pos;

	//��ԏ���΂�
	std::getline(fin, line);

	for (int i = 0; std::getline(fin, line); i++)
	{

		std::istringstream stream(line);
		std::string str;

		Pos.push_back(DirectX::SimpleMath::Vector3());

		std::getline(stream, str, ',');
		Pos.back().x =  std::stof(str);
		std::getline(stream, str, ',');
		Pos.back().y= std::stof(str);
		std::getline(stream, str, ',');
		Pos.back().z = std::stof(str);

		
	}


	fin.close();

	return Pos;
}








