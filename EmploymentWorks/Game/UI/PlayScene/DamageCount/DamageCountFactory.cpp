#include "pch.h"
#include "DamageCountFactory.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/UI/PlayScene/DamageCount/DamageCount.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "GameBase/Component/Components.h"
#include "Game/MathUtil.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Camera/Camera.h"

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

	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::ENEMY_DAMAGE
		}, this
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

					//���W���X�N���[�����W�ɕϊ�
					auto ScreenPos = MathUtil::WorldToScreen(data.Position,
						DirectX::SimpleMath::Matrix::Identity,
						GetScene()->GetCamera()->GetViewMatrix(),
						GetScene()->GetCamera()->GetProjectionMatrix()
					);


					ui->GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(ScreenPos.x,ScreenPos.y,0));

					break;
				}
			}

			break;
		default:
			break;
	}

}
