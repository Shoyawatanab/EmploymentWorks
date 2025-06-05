/*
�X�e�[�W�쐬�N���X
*/


#pragma once
#include "GameBase/Actor.h"

class StageFactory : public Actor
{
public:

	struct StageParameter
	{
		DirectX::SimpleMath::Vector3 Scale;
		DirectX::SimpleMath::Vector3 Position;
		DirectX::SimpleMath::Quaternion Rotation;
	};

public:
	//�R���X�g���N�^
	StageFactory(Scene* scene);
	//�f�X�g���N�^
	~StageFactory() override ;

private:

	//�X�e�[�W�f�[�^�̓ǂݍ���
	void LoadStageData();

};