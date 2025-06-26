#include "pch.h"
#include "TargetMarker.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Screen.h"
#include "GameBase/Camera/Camera.h"
#include "GameBase/Actor.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/MathUtil.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="canvas">�L�����o�X</param>
/// <param name="targets">�^�[�Q�b�g�z��</param>
TargetMarker::TargetMarker(Canvas* canvas, std::vector<Actor*> targets)
	:
	Actor(canvas->GetScene())
	,m_marker{}
	,m_targets{targets}
	,m_isGetReady{false}
	,m_isLockOn{false}
{

	using namespace DirectX::SimpleMath;

	m_marker = GetScene()->AddActor<Image>(canvas,"TargetMarker");
	///m_marker->SetActive(false);
	m_marker->GetTransform()->SetScale(SCALE);

	m_marker->GetTransform()->SetPosition(Vector3::Zero);
	m_marker->SetActive(false);

	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::PLAYER_GET_REDAY
			,SceneMessageType::PLAYER_GET_REDAY_END
		}
		, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TargetMarker::~TargetMarker()
{
}

/// <summary>
/// �P�̂̍X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void TargetMarker::UpdateActor(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	if (!m_isGetReady) { return; }

	Vector2 result = FilterWithinRange();

	m_marker->GetTransform()->SetPosition(Vector3(result.x, result.y, 0.0f));



}


void TargetMarker::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::NONE:
			break;
		case SceneMessageType::PLAYER_GET_REDAY:
			m_isGetReady = true;
			break;
		case SceneMessageType::PLAYER_GET_REDAY_END:
			m_isGetReady = false;
			m_marker->SetActive(false);
			break;
		default:
			break;
	}
}

/// <summary>
/// �͈͓����ǂ���������
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Vector2 TargetMarker::FilterWithinRange()
{

	using namespace DirectX::SimpleMath;
	//�ϐ��錾
	DirectX::SimpleMath::Vector2 result;

	m_marker->SetActive(false);
	m_isLockOn = false;

	//��ʂ̉��̃T�C�Y�������l�Ƃ���
	float minLength = Screen::WIDTH;


	//
	for (const auto& point : m_targets)
	{
		//���W���X�N���[�����W�ɕϊ�
		Vector2 ScreenPos = MathUtil::WorldToScreen(point->GetTransform()->GetWorldPosition(),
			Matrix::Identity,
			GetScene()->GetCamera()->GetViewMatrix(),
			GetScene()->GetCamera()->GetProjectionMatrix()
		);

		float distance = Vector2::Distance(ScreenPos, Vector2(Screen::CENTER_X,Screen::CENTER_Y));

		//raneg���̍��W���ǂ����̔���
		if (distance <= RANGE)
		{
			//�ŏ��l�������������
			if (minLength > distance)
			{

				//�z��Ɋi�[
				result = ScreenPos;
				//�ŏ��l���X�V
				minLength = distance;
				//�^�[�Q�b�g���X�V
				m_targetPosition = point->GetTransform()->GetWorldPosition();

				m_marker->SetActive(true);
				m_isLockOn = true;
			}

		}
	}

	return result;
}

