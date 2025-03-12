/*
	@file	Score.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Score.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Score::Score()
	:
	m_commonResources{},
	m_position{},
	m_scale{}
	,m_score{}
	,m_digit{}
	,m_spriteBatch{}
	,m_time{}
	,m_width{}
	,m_height{}
	,m_digitCount{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Score::~Score()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Score::Initialize(CommonResources* resources)
{

	m_commonResources = resources;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// �X�v���C�g�o�b�`���쐬����
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);

	CreateNumberTex(L"Resources/Textures/Number.png", m_texture);


	m_width = 120;   //��
	m_height = 142;   //����

	m_position = Vector2(800, 360);
	m_scale = Vector2::One;
	
	Reset();

	m_score = 999;
	
}



/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Score::Update(float elapsedTime)
{

	float ratio = m_time / ANIMATION_TIME;

	ratio = std::min(ratio, 1.0f);

	int score = m_score * ratio;

	SplitDigits(score);	

	m_time += elapsedTime;

}


/// <summary>
/// �`��
/// </summary>
void Score::Render()
{
	//1����
	OneNumberRender(m_digit[3], Vector2(m_position.x - NUMBER_SPACINT * 1.5f, m_position.y), m_scale);
	//2����
	OneNumberRender(m_digit[2], Vector2(m_position.x - NUMBER_SPACINT / 2, m_position.y), m_scale);
	//3����
	OneNumberRender(m_digit[1], Vector2(m_position.x + NUMBER_SPACINT / 2, m_position.y), m_scale);
	//4����
	OneNumberRender(m_digit[0], Vector2(m_position.x + NUMBER_SPACINT * 1.5f, m_position.y), m_scale);

}

void Score::Reset()
{

	m_time = 0.0f;
	
	for (auto& digit : m_digit)
	{
		digit = 0;
	}

}

void Score::CreateNumberTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex)
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	//�摜�̓ǂݍ���
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			szFileName,
			nullptr,
			tex.ReleaseAndGetAddressOf()
		)
	);
}


void Score::OneNumberRender(int number, DirectX::SimpleMath::Vector2 Pos, DirectX::SimpleMath::Vector2 Scale)
{
	auto states = m_commonResources->GetCommonStates();


	// �X�v���C�g�o�b�`�̊J�n�F�I�v�V�����Ń\�[�g���[�h�A�u�����h�X�e�[�g���w�肷��
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	//���̔ԍ����Ƃ̕��ƍ������K�v
	float Width = 120;   //��
	float Hight = 142;   //����

	RECT NumberRECT{ 0 + number * static_cast<LONG>(Width), 1,
			110 + number * static_cast<LONG>(Width), static_cast<LONG>(Hight) };

	//PushSpace�̕`��
	m_spriteBatch->Draw(
		m_texture.Get(),	// �e�N�X�`��(SRV)
		Pos,				// �X�N���[���̕\���ʒu(origin�̕`��ʒu)
		&NumberRECT,			// ��`(RECT)
		Colors::White,		// �w�i�F
		0.0f,				// ��]�p(���W�A��)
		Vector2(Width / 2, Hight / 2),		// �e�N�X�`���̊�ɂȂ�\���ʒu(�`�撆�S)(origin)
		Scale,				// �X�P�[��(scale)
		SpriteEffects_None,	// �G�t�F�N�g(effects)
		0.0f				// ���C���[�x(�摜�̃\�[�g�ŕK�v)(layerDepth)
	);

	// �X�v���C�g�o�b�`�̏I���
	m_spriteBatch->End();


}

void Score::SplitDigits(int number)
{

	m_digitCount =  static_cast<int>( std::log10(std::abs(number))) + 1;

	for (int i = 0; i < m_digitCount; i++)
	{
		m_digit[i] = number % 10;

		number /= 10;
	}

}

