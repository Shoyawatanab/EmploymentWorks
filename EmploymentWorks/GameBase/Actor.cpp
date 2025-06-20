#include"pch.h"
#include"Actor.h"

#include"Component/Transform/Transform.h"
#include "GameBase/Scene/Scene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene"></param>
Actor::Actor(Scene* scene)
	:
	m_scene{scene},
	m_components{},
	m_transform{nullptr},
	m_isActive{true},
	m_isDestroy{false},
	m_isComponentDestroy{false}
{
	m_transform = AddComponent<Transform>(this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Actor::~Actor()
{
	m_components.clear();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Actor::Update(const float& deltaTime)
{
	if (!m_isActive) { return; }

	// �R���|�[�l���g�X�V����
	UpdateComponent(deltaTime);
	// �R���|�[�l���g�ʃA�b�v�f�[�g
	UpdateActor(deltaTime);
	// �R���|�[�l���g�폜
	RemoveComponent();
}

/// <summary>
/// �R���|�[�l���g�X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Actor::UpdateComponent(const float& deltaTime)
{
	// �R���|�[�l���g����
	for (auto& component : m_components)
	{
		// �R���|�[�l���g�A�N�e�B�u
		if (!component->GetActive()) { continue; }
		component->Update(deltaTime);
	}
}



/// <summary>
/// �폜
/// </summary>
void Actor::Destroy()
{

	// �A�N�^�[�̔j�󏈗����I���ɂ���
	GetScene()->ActorDestroyOn();

}

/// <summary>
/// �j�󂷂�R���|�[�l���g���������āA�폜
/// </summary>
void Actor::RemoveComponent()
{
	// �j��\�����Ȃ��Ȃ�Ԃ�
	if (m_isComponentDestroy) { return; }
	// �폜�v�f��r������
	m_components.erase(std::remove_if(m_components.begin(), m_components.end(),
		[&](std::unique_ptr<Component>& comp)
		{
			// �Ή��R���|�[�l���g�̔j�󏈗����Ă�
			return comp->GetIsDestroy();
		}), m_components.end());
	// �j��v�����I�t�ɂ���
	m_isComponentDestroy = true;
}

/// <summary>
/// �A�N�e�B�u�t���O�ύX
/// </summary>
/// <param name="active"></param>
void Actor::SetActive(bool active)
{
	// �A�N�e�B�u��Ԃ̑��
	m_isActive = active;
	// �q�֓`�d������
	for (auto& children : m_transform->GetAllChild())
	{
		children->GetActor()->SetActive(active);
	}
	// �R���|�[�l���g
	for (auto& component : m_components)
	{
		component.get()->SetActive(active);
	}

	//���ʂɉ������֐����Ă�
	if (active)
	{
		OnEnable();
	}
	else
	{
		OnDisable();
	}

}