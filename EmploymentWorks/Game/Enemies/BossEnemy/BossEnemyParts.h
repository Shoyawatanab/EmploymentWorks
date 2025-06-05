#pragma once
#include "GameBase/Actor.h"



class BossEnemyParts : public Actor
{
public:

	//���O�̎擾
	std::string  GetPartsName() const { return m_partsName; }


public:
	//�R���X�g���N�^
	BossEnemyParts(Scene* scene, std::string partsName, std::string modelName);
	//�f�X�g���N�^
	~BossEnemyParts() override  ;

private:
	//�p�[�c��
	std::string m_partsName;


};