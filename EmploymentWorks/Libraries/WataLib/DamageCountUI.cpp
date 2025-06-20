/*
	@file	DamageCountUI.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "DamageCountUI.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>


#include "Libraries/MyLib/DebugString.h"
#include "Libraries/WataLib/UserInterface.h"
#include "Libraries/WataLib/DrawNumber.h"



void WataLib::DamageCountUI::SetPosition(const DirectX::SimpleMath::Vector3& Pos)
{
	 m_position = Pos;
}

void WataLib::DamageCountUI::SetScale(const DirectX::SimpleMath::Vector2& scale)
{
	m_scale = scale;
	m_backGraund->SetScale(m_scale);
	m_numberUI->SetScale(m_scale);
}

void WataLib::DamageCountUI::SetRotate(const float& rotate)
{
	m_rotate = rotate;
	m_backGraund->SetRenderRatio(rotate);
}


void WataLib::DamageCountUI::SetDamage(const int& damage)
{

	m_damage = damage;


	m_digitNumber.clear();

	//�Q�����邩�ǂ���
	if (m_damage >= 10)
	{
		std::pair<int, DirectX::SimpleMath::Vector2> datas;

		//2����
		datas.first = m_damage / 10;
		datas.second = DirectX::SimpleMath::Vector2(-DIGITWIDTH, 0);

		m_digitNumber.push_back(datas);

		//1����
		datas.first = m_damage % 10;
		datas.second = DirectX::SimpleMath::Vector2(DIGITWIDTH, 0);

		m_digitNumber.push_back(datas);

	}
	else
	{
		std::pair<int, DirectX::SimpleMath::Vector2> datas;

		//�P����
		datas.first = m_damage % 10;
		datas.second = DirectX::SimpleMath::Vector2::Zero;

		m_digitNumber.push_back(datas);

	}

}

void WataLib::DamageCountUI::SetScreenPosition(const DirectX::SimpleMath::Vector2& position)
{

	m_screenPosition = position;

	m_backGraund->SetPosition(m_screenPosition);
	m_numberUI->SetPosition(m_screenPosition);

}


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources"></param>
WataLib::DamageCountUI::DamageCountUI(CommonResources* resources)
	:
	m_commonResources{resources},
	m_texture{},
	m_texCenter{},
	m_position{},
	m_scale{},
	m_rotate{}
	,m_backGraund{}
	,m_numberUI{}
	,m_damage{}
	,m_screenPosition{}
	,m_isActive{false}
	,m_digitNumber{}
	,m_time{}
{

	m_numberUI = std::make_unique<DrawNumber>();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WataLib::DamageCountUI::~DamageCountUI()
{
	// do nothing.


}

/// <summary>
/// ������
/// </summary>
void WataLib::DamageCountUI::Initialize()
{

	using namespace DirectX::SimpleMath;

	m_backGraund = std::make_unique<UserInterface>();
	m_backGraund = LoadTexture("DamageBackGraund"
		, Vector2(640, 50)
		, Vector2(1.0f, 1.0f)
	);


	m_numberUI->Create(m_commonResources->GetDeviceResources(),
		L"Resources/Textures/Number.png"
		, Vector2::Zero
		, Vector2::One);

	m_scale = Vector2(0.1f, 0.1f);

	SetPosition(m_position);
	SetScale(m_scale);

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void WataLib::DamageCountUI::Update(const float& elapsedTime)
{

	if (!m_isActive)
	{
		return;
	}

	if (m_time >= MAXTIME)
	{

		m_isActive = false;
		m_time = 0;
		return;
	}


	m_time += elapsedTime;

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void WataLib::DamageCountUI::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX::SimpleMath;

	if (!m_isActive)
	{
		return;
	}

	//���W���X�N���[�����W�ɕϊ����ēo�^
	SetScreenPosition(WorldToScreen(m_position,
		Matrix::Identity, view, projection, Screen::WIDTH, Screen::HEIGHT));

	m_backGraund->Render();
	
	m_damage = 1;
	
	for (int i = 0; i < m_digitNumber.size(); i++)
	{
		m_numberUI->Render(m_digitNumber[i].first % 10,m_digitNumber[i].second);
	}



}

void WataLib::DamageCountUI::Finalize()
{
	// do nothing.

}

/// <summary>
/// �摜�̓ǂݍ���
/// </summary>
/// <param name="key"></param>
/// <param name="position"></param>
/// <param name="scale"></param>
/// <returns></returns>
std::unique_ptr<UserInterface> WataLib::DamageCountUI::LoadTexture(std::string key, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale)
{
	//  ���j���[�Ƃ��ăA�C�e����ǉ�����
	std::unique_ptr<UserInterface> userInterface = std::make_unique<UserInterface>();
	//  �w�肳�ꂽ�摜��\�����邽�߂̃A�C�e�����쐬����
	userInterface->Create(m_commonResources
		, key
		, position
		, scale
	);

	return userInterface;
}

/// <summary>
/// ���[���h���W���X�N���[�����W�ɕϊ�
/// </summary>
/// <param name="worldPos">���[���h���W</param>
/// <param name="worldMatrix">���[���h�s��</param>
/// <param name="viewMatrix">�r���[�s��</param>
/// <param name="projectionMatrix">�ˉe�s��</param>
/// <param name="screenWidth">��ʂ̉��̒���</param>
/// <param name="screenHeight">��ʂ̏c�̒���</param>
/// <returns>�X�N���[�����W</returns>
DirectX::SimpleMath::Vector2 WataLib::DamageCountUI::WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos, const DirectX::SimpleMath::Matrix& worldMatrix, const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix, int screenWidth, int screenHeight)
{
	using namespace DirectX::SimpleMath;
	// ���[���h���W��ϊ����邽�߂̍s�������
	Matrix transformMatrix = worldMatrix * viewMatrix * projectionMatrix;

	// ���[���h���W���v���W�F�N�V������Ԃɕϊ�
	Vector3 projectedPos = Vector3::Transform(worldPos, transformMatrix);

	// �ˉe���ꂽ���W���X�N���[�����W�ɕϊ�
	float x = (projectedPos.x / projectedPos.z * 0.5f + 0.5f) * screenWidth;
	float y = (0.5f - projectedPos.y / projectedPos.z * 0.5f) * screenHeight;

	return Vector2(x, y);
}




