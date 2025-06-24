#include "pch.h"
#include "WeaponManager.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Messenger/Messenger.h"



WeaponManager::WeaponManager(Scene* scene, Player* player)
	:
	Actor(scene)
	,m_boomerangs{}
	, m_holdWeapon{}
{

	//�u�[���������쐬
	for (int i = 0; i < 3; i++)
	{
		auto boomerang = GetScene()->AddActor<Boomerang>(scene, player);
		m_boomerangs.push_back(boomerang);
	}

	//���b�Z���W���[�ɓo�^
	Messenger::GetInstance()->Rigister(
		{
			MessageType::BOOMERANG_IDEL_STATE
			,MessageType::BOOMERANG_GET_READY_STATE
			,MessageType::BOOMERANG_THROW_STATE
		}
		, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WeaponManager::~WeaponManager()
{
}

/// <summary>
/// �P�̍X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void WeaponManager::UpdateActor(const float& deltaTime)
{

}

/// <summary>
/// �ʒm���ɌĂяo�����֐�
/// </summary>
/// <param name="type"></param>
/// <param name="datas"></param>
void WeaponManager::Notify(MessageType type, void* datas)
{

	switch (type)
	{
		case MessageType::BOOMERANG_IDEL_STATE:
		{

			//��Ɏ����Ă�����@�@�\���Ă���Ƃ���IDEL�ύX
			if (m_holdWeapon)
			{
				//��Ԃ̕ύX
				m_holdWeapon->ChangeState(WeaponBase::WeaponState::BOOMERANG_IDLE);
				m_holdWeapon = nullptr;
			}
			//�f�[�^�����邩�@�@�@�@�@�@THROW�����IDEL�ύX
			if (datas != nullptr)
			{
				//�f�[�^�̃L���X�g
				auto boomerang = static_cast<Boomerang*>(datas);
				//�������L���X�g�ł��Ă��邩
				if (typeid(*boomerang) == typeid(Boomerang))
				{
					boomerang->ChangeState(WeaponBase::WeaponState::BOOMERANG_IDLE);
				}
			}

		}
			break;
		case MessageType::BOOMERANG_GET_READY_STATE:
			//�ʏ��Ԃ̃u�[��������T��
			m_holdWeapon = GetBoomerang(WeaponBase::WeaponState::BOOMERANG_IDLE);
			if (m_holdWeapon)
			{
				//��Ԃ̕ύX
				m_holdWeapon->ChangeState(WeaponBase::WeaponState::BOOMERANG_GET_READY);

			}
			break;
		case MessageType::BOOMERANG_THROW_STATE:
			if (!m_holdWeapon) { return; }
			//��Ԃ̕ύX
			m_holdWeapon->ChangeState(WeaponBase::WeaponState::BOOMERANG_THROW);
			m_holdWeapon = nullptr;
			break;
		default:
			break;
	}

}

/// <summary>
/// �����Ԃ̃u�[�������P���̎擾
/// </summary>
/// <param name="getState">�~�������</param>
/// <returns>�u�[�������N���X</returns>
Boomerang* WeaponManager::GetBoomerang(WeaponBase::WeaponState getState)
{

	for (auto& boomerang : m_boomerangs)
	{
		if (boomerang->GetWeaponState() == getState)
		{
			return boomerang;
		}
	}

	return nullptr;
}
