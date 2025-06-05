#include "pch.h"
#include "ModelBase.h"
#include "GameBase/Component/Components.h"




ModelBase::ModelBase(Scene* scene, std::string partsName, std::string modelName)
	:
	Actor(scene)
	, m_partsName{ partsName }
{

	AddComponent<ModelComponent>(this, modelName);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ModelBase::~ModelBase()
{
}

/// <summary>
/// �e�̓o�^
/// </summary>
/// <param name="parent">�e</param>
void ModelBase::SetParent(ModelBase* parent)
{
	//�e�����Ȃ��ꍇ
	if (parent == nullptr)
	{
		//�e������ꍇ
		if (m_parent != nullptr)
		{
			//�e����̉���
			m_parent->RemoveChild(this);
			m_parent = nullptr;
		}
		//�g�����X�t�H�[�����e�̓o�^������
		GetTransform()->SetParent(nullptr);

	}
	else
	{
		//���݂ƈႤ�e�̏ꍇ
		if (m_parent != parent)
		{
			//�e�̐ݒ�
			m_parent = parent;
			m_parent->SetChild(this);
		}
		//�g�����X�t�H�[�����e�̓o�^������
		GetTransform()->SetParent(parent->GetTransform());

	}


}

/// <summary>
/// ���g���܂߂��q�����f����S�ĕԂ�
/// </summary>
/// <returns></returns>
std::vector<ModelBase*> ModelBase::GetAllDescendants()
{
	//�i�[�ϐ�
	std::vector<ModelBase*> modelBases;
	//�������g���ǉ�����
	modelBases.push_back(this);
	//�q�����f����T��
	CollentDescendants(this, modelBases);

	return modelBases;
}

/// <summary>
/// �q�̍폜
/// </summary>
/// <param name="child">�q</param>
void ModelBase::RemoveChild(ModelBase* child)
{

	//�q��T��
	auto serchChild = std::find(m_child.begin(), m_child.end(), child);

	//�����
	if (serchChild != m_child.end())
	{
		//�q�̍폜
		m_child.erase(serchChild);

	}


}

/// <summary>
/// �ċA�I�Ɏq�����f����Ԃ�
/// </summary>
/// <param name="node"></param>
/// <param name="modelBases"></param>
void ModelBase::CollentDescendants(ModelBase* node, std::vector<ModelBase*>& modelBases)
{
	//�q�m�[�h
	for (auto& child : node->GetAllChild())
	{
		//�g�����X�t�H�[���Ɋi�[
		modelBases.push_back(child);
		//�q�̎q��T���ĕԂ�
		CollentDescendants(child, modelBases);
	}

}






