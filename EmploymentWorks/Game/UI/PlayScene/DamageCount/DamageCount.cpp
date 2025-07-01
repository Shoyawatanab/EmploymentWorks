#include "pch.h"
#include "DamageCount.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Component/Components.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "Game/UI/NumberUI.h"

DamageCount::DamageCount(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_backGraund{}
	,m_numbers{}
	,m_usedNumbers{}
	,m_time{}
{
	using namespace DirectX::SimpleMath;


	////�w�i�摜
	m_backGraund = GetScene()->AddActor<Image>(canvas,"DamageBackGraund");
	m_backGraund->GetTransform()->SetScale(BACKGROUND_SCALE);
	m_backGraund->GetTransform()->SetParent(GetTransform());

	//����
	for (int i = 0; i < MAXDIGITS; i++)
	{
		auto number = GetScene()->AddActor<NumberUI>(canvas);
		number->GetTransform()->SetScale(Vector3(0.1f, 0.1f,0));
		number->GetTransform()->SetParent(GetTransform());
		number->SetActive(false);
		m_numbers.push_back(number);
	}

	GetTransform()->SetScale(Vector3(0.1, 0.1, 0));
	//GetTransform()->SetPosition(Vector3(640, 360, 0));

	//�������Ŕ�A�N�e�B�u��
	SetActive(false);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DamageCount::~DamageCount()
{
}

/// <summary>
/// �P�̍X�V
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void DamageCount::UpdateActor(const float& deltaTime)
{

	if (m_time >= DISPLAYTIME)
	{
		SetActive(false);
		m_time = 0.0f;
		return;
	}

	m_time += deltaTime;
}

/// <summary>
/// �I�u�W�F�N�g���A�N�e�B�u�ɂȂ������ɌĂ΂��֐�
/// </summary>
void DamageCount::OnEnable()
{

	//�ԍ������ׂĔ�A�N�e�B�u��
	for (auto& number : m_numbers)
	{
		number->SetActive(false);
	}

}

/// <summary>
/// �I�u�W�F�N�g����A�N�e�B�u�ɂȂ������ɌĂ΂��֐�
/// </summary>
void DamageCount::OnDisable()
{

	//������
	m_usedNumbers.clear();



}


void DamageCount::SetDamage(int damage)
{
	using namespace DirectX::SimpleMath;

	//���������߂�
	int digits = std::log10(damage) + 1;

	//�ő包���𒴂��Ă�����\�����Ȃ�
	if (digits > MAXDIGITS)
	{
		return;
	}



	//����������
	for (int i = digits - 1; i >= 0; --i)
	{
		//�\���ԍ��̃Z�b�g
		auto number = m_numbers[i];
		number->SetNumber(damage % 10);

		//�\�����W�̐ݒ�
		float offsetX = (i - (digits - 1) / 2.0f) * SPACING;

		Vector3 pos = Vector3(offsetX, 0, 0);

		number->GetTransform()->SetPosition(pos);
		number->SetActive(true);

		m_usedNumbers.push_back(number);

		damage /= 10;
	}


}
