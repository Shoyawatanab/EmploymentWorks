/*
	�N���X��     : DamageCountFactory
	����         : �_���[�WUI�̍쐬�N���XI
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "DamageCountFactory.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/UI/PlayScene/DamageCount/DamageCount.h"
#include "Game/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Camera/Camera.h"
#include "Game/Messenger/Messengers.h"


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
DamageCountFactory::DamageCountFactory(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_damageCount{}
{
	//�萔�����O�ɍ쐬
	for (int i = 0; i < MAX; i++)
	{
		auto damageCount = GetScene()->AddActor<DamageCount>(canvas);
		m_damageCount.push_back(damageCount);
	}

	//�ʒm���󂯎��R���|�[�l���g�̒ǉ�
	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	//�ǂ̒ʒm���̓o�^�ƌĂяo���֐��̓o�^
	ob->Rigister(
		{
			SceneMessageType::ENEMY_DAMAGE
		}
		, std::bind(&DamageCountFactory::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DamageCountFactory::~DamageCountFactory()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void DamageCountFactory::Notify(SceneMessageType type, void* datas)
{

	switch (type)
	{
		case SceneMessageType::ENEMY_DAMAGE:
			
			for (auto& ui : m_damageCount)
			{
				//��A�N�e�B�u�Ȃ�
				if (!ui->GetActive())
				{
					//�A�N�e�B�u��
					ui->SetActive(true);

					EnemyDamageDatas data = *static_cast<EnemyDamageDatas*>(datas);

					//�ǉ��f�[�^����_���[�W���L���X�g
					ui->SetDamage(data.Damage);

					ui->SetWorldPosition(data.Position);

					break;
				}
			}

			break;
		default:
			break;
	}

}
