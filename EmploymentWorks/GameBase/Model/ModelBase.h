#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Model/ModelPartsBase.h"

class ModelBase : public Actor
{
public:
	//�p�[�c�̎擾
	std::unordered_map<std::string, ModelPartsBase*>& GetParts() { return m_parts; }

public:
	//�R���X�g���N�^
	ModelBase(Scene* scene);
	//�f�X�g���N�^
	~ModelBase();

	//�p�[�c�̓o�^
	void AddParts(std::vector<ModelPartsBase*> partss);

private:

	//�p�[�c
	std::unordered_map<std::string, ModelPartsBase*> m_parts;

};