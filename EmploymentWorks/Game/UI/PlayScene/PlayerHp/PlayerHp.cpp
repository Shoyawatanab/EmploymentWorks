#include "pch.h"
#include "PlayerHp.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/UI/Image.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
PlayerHp::PlayerHp(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{

	using namespace DirectX::SimpleMath;


	auto image1 = GetScene()->AddActor<Image>(canvas, "HP");
	image1->GetTransform()->SetParent(GetTransform());

	image1->GetTransform()->SetScale(HEART_SCALE);
	image1->GetTransform()->SetPosition(-OFFSET_POSITION);

	auto image2 = GetScene()->AddActor<Image>(canvas, "HP");
	image2->GetTransform()->SetParent(GetTransform());

	image2->GetTransform()->SetScale(HEART_SCALE);
	image2->GetTransform()->SetPosition(Vector3::Zero);

	auto image3 = GetScene()->AddActor<Image>(canvas, "HP");
	image3->GetTransform()->SetParent(GetTransform());

	image3->GetTransform()->SetScale(HEART_SCALE);
	image3->GetTransform()->SetPosition(OFFSET_POSITION);


	m_heart.push_back(image1);
	m_heart.push_back(image2);
	m_heart.push_back(image3);

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITION);


	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::PLAYER_DAMAGE
		}, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerHp::~PlayerHp()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void PlayerHp::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::PLAYER_DAMAGE:
			//�z��̌�납��T��
			for (int i = static_cast<int>( m_heart.size() - 1); i >= 0; --i)
			{
				//�A�N�e�B�u��Ԃ̂��̂������
				if (m_heart[i]->GetActive())
				{
					//��A�N�e�B�u��
					m_heart[i]->SetActive(false);
					break;
				}
			}
			break;
		default:
			break;
	}
}

