/*
	�p�[�c���f���̊��N���X�@�ǂ�ȃp�[�c���f���ł��p������
*/

#pragma once
#include "GameBase/Actor.h"


class ModelPartsBase : public Actor
{
public:

	//���O�̎擾
	std::string  GetPartsName() const { return m_partsName; }
	//�S�Ẵp�[�c�̎擾
	const std::vector<ModelPartsBase*>& GetAllChild() { return m_child; }

	void SetParent(ModelPartsBase* parent);

	//���g���܂߂��q�����f����S�Ă�Ԃ�
	std::vector<ModelPartsBase*> GetAllDescendants();

private:
	
	void SetChild(ModelPartsBase* child) { m_child.push_back(child); };
	//�q�̍폜
	void RemoveChild(ModelPartsBase* child);

	//�ċA�G�Ɏq��Ԃ��֐�
	void CollentDescendants(ModelPartsBase* node, std::vector<ModelPartsBase*>& ModelPartsBase);


public:

	//�R���X�g���N�^
	ModelPartsBase(Scene* scene, const std::string& partsName, const std::string& modelName);
	//�f�X�g���N�^
	~ModelPartsBase();



private:
	//�p�[�c��
	std::string m_partsName;
	//�q�I�u�W�F�N�g
	std::vector<ModelPartsBase*>m_child;
	//�e���f��
	ModelPartsBase* m_parent;

};
