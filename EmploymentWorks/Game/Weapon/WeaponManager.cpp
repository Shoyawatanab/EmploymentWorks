/*
	�N���X��     : WeaponManager
	����         : ����̃}�l�[�W���[
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "WeaponManager.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"


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

	//�ʒm���󂯎��R���|�[�l���g�̒ǉ�
	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	//�ǂ̒ʒm���̓o�^�ƌĂяo���֐��̓o�^
	ob->Rigister(
		{
			SceneMessageType::BOOMERANG_IDEL_STATE
			,SceneMessageType::BOOMERANG_GET_READY_STATE
			,SceneMessageType::BOOMERANG_THROW_STATE
		}
		, std::bind(&WeaponManager::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WeaponManager::~WeaponManager()
{
}



/// <summary>
/// �ʒm���ɌĂяo�����֐�
/// </summary>
/// <param name="type"></param>
/// <param name="datas"></param>
void WeaponManager::Notify(SceneMessageType type, void* datas)
{

	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::BOOMERANG_IDEL_STATE:
			//��Ɏ����Ă�����@�@�\���Ă���Ƃ���IDEL�ύX
			if (m_holdWeapon)
			{
				//��Ԃ̕ύX
				m_holdWeapon->ChangeState(BoomerangState::IDEL);
				m_holdWeapon = nullptr;
			}
			break;
		case SceneMessageType::BOOMERANG_GET_READY_STATE:
			//�ʏ��Ԃ̃u�[��������T��
			m_holdWeapon = GetBoomerang(BoomerangState::IDEL);
			//�k���łȂ��ꍇ
			if(m_holdWeapon)
			{
				//��Ԃ̕ύX
				m_holdWeapon->ChangeState(BoomerangState::GET_READY);
			}
			break;
		case SceneMessageType::BOOMERANG_THROW_STATE:
			//�\���Ă���ꍇ
			if (!m_holdWeapon) { return; }
			//��Ԃ̕ύX
			m_holdWeapon->ChangeState(BoomerangState::THROW);
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
Boomerang* WeaponManager::GetBoomerang(BoomerangState getState)
{

	for (auto& boomerang : m_boomerangs)
	{
		if (boomerang->GetState() == getState)
		{
			return boomerang;
		}
	}

	return nullptr;
}
