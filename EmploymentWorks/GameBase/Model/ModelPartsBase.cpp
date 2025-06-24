#include "pch.h"
#include "ModelPartsBase.h"
#include "GameBase/Component/Components.h"




ModelPartsBase::ModelPartsBase(Scene* scene, const std::string& partsName, const std::string& modelName)
	:
	Actor(scene)
	, m_partsName{ partsName }
	,m_parent{}
{

	//�R���|�[�l���g�̒ǉ�
	AddComponent<ModelComponent>(this, modelName);
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ModelPartsBase::~ModelPartsBase()
{
}

/// <summary>
/// �e�̓o�^
/// </summary>
/// <param name="parent">�e</param>
void ModelPartsBase::SetParent(ModelPartsBase* parent)
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
std::vector<ModelPartsBase*> ModelPartsBase::GetAllDescendants()
{
	//�i�[�ϐ�
	std::vector<ModelPartsBase*> ModelPartsBases;
	//�������g���ǉ�����
	ModelPartsBases.push_back(this);
	//�q�����f����T��
	CollentDescendants(this, ModelPartsBases);

	return ModelPartsBases;
}

/// <summary>
/// �q�̍폜
/// </summary>
/// <param name="child">�q</param>
void ModelPartsBase::RemoveChild(ModelPartsBase* child)
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
/// <param name="ModelPartsBases"></param>
void ModelPartsBase::CollentDescendants(ModelPartsBase* node, std::vector<ModelPartsBase*>& ModelPartsBases)
{
	//�q�m�[�h
	for (auto& child : node->GetAllChild())
	{
		//�g�����X�t�H�[���Ɋi�[
		ModelPartsBases.push_back(child);
		//�q�̎q��T���ĕԂ�
		CollentDescendants(child, ModelPartsBases);
	}

}






