#include "pch.h"
#include "BoomerangCount.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
BoomerangCount::BoomerangCount(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	using namespace DirectX::SimpleMath;


	//�^�񒆂�UI���[�����W�ɂȂ�悤�ɂ��Ă���

	auto image1 = GetScene()->AddActor<Image>(canvas, "BoomerangUI");
	image1->GetTransform()->SetParent(GetTransform());

	image1->GetTransform()->SetScale(BOOMERANG_SCALE);
	image1->GetTransform()->SetPosition(-OFFSET_POSITION);
	
	m_boomerangUI.push_back(image1);

	auto image2 = GetScene()->AddActor<Image>(canvas, "BoomerangUI");
	image2->GetTransform()->SetParent(GetTransform());

	image2->GetTransform()->SetScale(BOOMERANG_SCALE);
	image2->GetTransform()->SetPosition(Vector3::Zero);

	m_boomerangUI.push_back(image2);

	auto image3 = GetScene()->AddActor<Image>(canvas, "BoomerangUI");
	image3->GetTransform()->SetParent(GetTransform());

	image3->GetTransform()->SetScale(BOOMERANG_SCALE);
	image3->GetTransform()->SetPosition(OFFSET_POSITION);

	m_boomerangUI.push_back(image3);


	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITION);

	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::BOOMERANG_THROW
			,SceneMessageType::BOOMERANG_CATCH
		}, this
	);



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangCount::~BoomerangCount()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void BoomerangCount::Notify(SceneMessageType type, void* datas)
{

	switch (type)
	{
		case SceneMessageType::BOOMERANG_THROW:
			//�z��̌�납��T��
			for (int i = static_cast<int>( m_boomerangUI.size() - 1); i >= 0; --i)
			{
				//�A�N�e�B�u��Ԃ̂��̂������
				if (m_boomerangUI[i]->GetActive())
				{
					//��A�N�e�B�u��
					m_boomerangUI[i]->SetActive(false);
					break;
				}
			}
			break;
		case SceneMessageType::BOOMERANG_CATCH:
			//�z�񏇂ɉ�
			for (int i = 0 ; i < m_boomerangUI.size(); i++)
			{
				//��A�N�e�B�u��Ԃ̂��̂������
				if (!m_boomerangUI[i]->GetActive())
				{
					//�A�N�e�B�u��
					m_boomerangUI[i]->SetActive(true);
					break;
				}
			}
			break;
		default:
			break;
	}

}
