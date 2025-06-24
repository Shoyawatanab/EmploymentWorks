#include "pch.h"
#include "RigidbodyManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
RigidbodyManager::RigidbodyManager()
	:
	m_rigidbody{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RigidbodyManager::~RigidbodyManager()
{
	m_rigidbody.clear();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"�o�ߎ���></param>
void RigidbodyManager::Update(const float& deltaTime)
{
	//���W�b�g�{�f�B�[�̍X�V
	for (auto& rigidbody : m_rigidbody)
	{
		if (!rigidbody->GetActive())
		{
			continue;
		}

		rigidbody->Update(deltaTime);
	}

}

/// <summary>
/// ���W�b�g�{�f�B�[�̒ǉ�
/// </summary>
/// <param name="rigidbody"></param>
void RigidbodyManager::AddRigidbody(RigidbodyComponent* comp)
{

	auto rigidbody = std::find(m_rigidbody.begin(), m_rigidbody.end(), comp);

	if (rigidbody == m_rigidbody.end())
	{
		m_rigidbody.push_back(std::move(comp));

	}
}

/// <summary>
/// ���W�b�g�{�f�B�[�̍폜
/// </summary>
/// <param name="rigidbody"></param>
void RigidbodyManager::RemoveRigidbody(RigidbodyComponent* comp)
{

	auto rigidbody = std::find(m_rigidbody.begin(), m_rigidbody.end(), comp);

	if (rigidbody != m_rigidbody.end())
	{

		m_rigidbody.erase(rigidbody);

	}


}
