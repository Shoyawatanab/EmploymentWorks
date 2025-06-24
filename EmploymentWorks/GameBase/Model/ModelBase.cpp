#include "pch.h"
#include "ModelBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
ModelBase::ModelBase(Scene* scene)
	:
	Actor(scene)
	,m_parts{}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ModelBase::~ModelBase()
{
	//�N���A
	m_parts.clear();

}

/// <summary>
/// �p�[�c�̓o�^
/// </summary>
/// <param name="partss">�p�[�c�z��</param>
void ModelBase::AddParts(std::vector<ModelPartsBase*> partss)
{
	for (auto& parts : partss)
	{
		//�p�[�c���̎擾
		auto name = parts->GetPartsName();
		//�o�^���ꂽ�p�[�c�������邩
		auto sertchParts = m_parts.find(name);
		//�����
		if (sertchParts != m_parts.end())
		{
			continue;
		}

		m_parts[name] = parts;


	}

}
