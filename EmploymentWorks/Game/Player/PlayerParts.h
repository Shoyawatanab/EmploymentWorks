#pragma once
#include "GameBase/Model/ModelPartsBase.h"


class PlayerParts  :public ModelPartsBase
{

public:

	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::PLAYER_PARTS; }

public:

	//�R���X�g���N�^
	PlayerParts(Scene* scene,std::string partsName,std::string modelName);
	//�f�X�g���N�^
	~PlayerParts() override;

private:



};