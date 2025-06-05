#pragma once
#include "GameBase/Model/ModelBase.h"
#include "GameBase/Scene/Scene.h"
#include <string>
#include <unordered_map>

class PlayerModel : public Actor
{
public:
	//�p�[�c�̎擾
	std::unordered_map<std::string, ModelBase*>& GetParts() { return m_parts; }


public:
	//�R���X�g���N�^
	PlayerModel(Scene* scene);
	//�ŃX�g�����O
	~PlayerModel();

	//�p�[�c�̓o�^
	void AddParts(std::vector<ModelBase*> parts);

private:

	//�p�[�c
	std::unordered_map<std::string, ModelBase*> m_parts;

};
