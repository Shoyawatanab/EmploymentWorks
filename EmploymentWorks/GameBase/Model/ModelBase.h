/*
	�p�[�c���f���̊��N���X�@�ǂ�ȃp�[�c���f���ł��p������
*/

#pragma once
#include "GameBase/Actor.h"

class ModelBase : public Actor
{
public:

	//���O�̎擾
	std::string  GetPartsName() const { return m_partsName; }
	//�S�Ẵp�[�c�̎擾
	const std::vector<ModelBase*>& GetAllChild() { return m_child; }

	void SetParent(ModelBase* parent);

	//���g���܂߂��q�����f����S�Ă�Ԃ�
	std::vector<ModelBase*> GetAllDescendants();

private:
	
	void SetChild(ModelBase* child) { m_child.push_back(child); };
	//�q�̍폜
	void RemoveChild(ModelBase* child);

	//�ċA�G�Ɏq��Ԃ��֐�
	void CollentDescendants(ModelBase* node, std::vector<ModelBase*>& modelBase);


public:

	//�R���X�g���N�^
	ModelBase(Scene* scene, std::string partsName, std::string modelName);
	//�f�X�g���N�^
	~ModelBase();



private:
	//�p�[�c��
	std::string m_partsName;
	//�q�I�u�W�F�N�g
	std::vector<ModelBase*>m_child;
	//�e���f��
	ModelBase* m_parent;

};
