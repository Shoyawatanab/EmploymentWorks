#include "pch.h"
#include "ResuktTime.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/UI/NumberUI.h"
#include "Game/UI/ResultScene/Time/TimeSeparator.h"
#include "Game/GlobalGameData.h"


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
ResuktTime::ResuktTime(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_time{}
{
	using namespace DirectX::SimpleMath;

	//�����̍쐬
	//����10�̈�
	auto number = GetScene()->AddActor<NumberUI>(canvas);
	number->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0));
	number->GetTransform()->SetPosition(Vector3(-LETTER_SPACING * 2,0, 0));
	number->GetTransform()->SetParent(GetTransform());
	m_numbers.push_back(number);
	
	//����1�̈�
	number = GetScene()->AddActor<NumberUI>(canvas);
	number->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0));
	number->GetTransform()->SetPosition(Vector3(-LETTER_SPACING,0, 0));
	number->SetNumber(1);
	number->GetTransform()->SetParent(GetTransform());
	m_numbers.push_back(number);
	
	// �b��10�̈�
	number = GetScene()->AddActor<NumberUI>(canvas);
	number->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0));
	number->GetTransform()->SetPosition(Vector3(LETTER_SPACING, 0, 0));
	number->SetNumber(1);
	number->GetTransform()->SetParent(GetTransform());
	m_numbers.push_back(number);

	// �b��1�̈�
	number = GetScene()->AddActor<NumberUI>(canvas);
	number->GetTransform()->SetScale(Vector3(0.1f, 0.1f, 0));
	number->GetTransform()->SetPosition(Vector3(LETTER_SPACING * 2, 0, 0));
	number->SetNumber(1);
	number->GetTransform()->SetParent(GetTransform());
	m_numbers.push_back(number);


	//��؂�_�̍쐬
	m_separator = GetScene()->AddActor<TimeSeparator>(canvas);
	m_separator->GetTransform()->SetParent(GetTransform());


	GetTransform()->SetPosition(POSITION);

	AddTime(GlobalGameData::GetInstance()->GetClearTime());

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResuktTime::~ResuktTime()
{
}

/// <summary>
/// �ʃA�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void ResuktTime::UpdateActor(const float& deltaTime)
{
	//�_��
	Blink(deltaTime);

}


/// <summary>
/// ���Ԃ̒ǉ�
/// </summary>
/// <param name="totalSecond"></param>
void ResuktTime::AddTime(const float& totalSeconds)
{

	//�������߂�
	int minutes = totalSeconds / 60;
	//�b�����߂�
	int seconds = static_cast<int>(totalSeconds) % 60;

	//�e���ɕ�������
	int minuteTens = minutes / 10;    // ����10�̈�
	int minuteOnes = minutes % 10;    // ����1�̈�

	int secondTens = seconds / 10;    // �b��10�̈�
	int secondOnes = seconds % 10;    // �b��1�̈�

	//���̃Z�b�g
	m_numbers[0]->SetNumber(minuteTens);
	m_numbers[1]->SetNumber(minuteOnes);

	//�b�̃Z�b�g
	m_numbers[2]->SetNumber(secondTens);
	m_numbers[3]->SetNumber(secondOnes);



}

/// <summary>
/// �_��
/// </summary>
/// <param name="deltaTime"></param>
void ResuktTime::Blink(const float& deltaTime)
{
	
	if (m_time >= BLINK_INTERVAL)
	{
		//���݂̏�Ԃ̎擾
		bool isActive = m_separator->GetActive();

		switch (isActive)
		{
			case true:
				//��A�N�e�B�u��Ԃ�
				m_separator->SetActive(false);
				break;
			case false:
				//�A�N�e�B�u��Ԃ�
				m_separator->SetActive(true);
				break;
			default:
				break;
		}

		m_time = 0.0f;
	}


	m_time += deltaTime;
}
