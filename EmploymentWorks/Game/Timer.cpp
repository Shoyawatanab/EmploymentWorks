/*
	@file	Timer.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Timer.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "StepTimer.h"


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Timer::Timer()
	:
	m_commonResources{},
	m_totalTime{},
	m_width{},
	m_height{},
	m_position{},
	m_scale{}

{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Timer::~Timer()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Timer::Initialize(CommonResources* resources)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	assert(resources);

	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// �X�v���C�g�o�b�`���쐬����
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);


	CreateNumberTex(L"Resources/Textures/Number.png", m_texture, m_texCenter);
	CreateTex(L"Resources/Textures/ten.png", m_tenTexture, m_tenTexCenter);
	CreateTex(L"Resources/Textures/TimeTex.png", m_timeTexture, m_timeTexCenter);


	//���̔ԍ����Ƃ̕��ƍ������K�v
	m_width = 120;   //��
	m_height = 142;   //����

	m_totalTime = 0;
	m_scale = 0.5f;
	m_position = Vector2(640, 320);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Timer::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);

	TimeCalculation();

	m_totalTime += elapsedTime;

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Timer::Render()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//�����̊Ԋu
	int a = 60;

	float gameTime = m_commonResources->GetStepTimer()->GetTotalSeconds();
	//2�b�𒴂�����0�ɖ߂�
	float t = fmodf(gameTime, 2.0f);


	TexRender(m_timeTexture, m_timeTexCenter, Vector2(m_position.x - a * 3, m_position.y), m_scale);
	OneNumberRender(m_minFirstDigit, Vector2(m_position.x - a * 2, m_position.y),m_scale);
	OneNumberRender(m_minSecondDigit, Vector2(m_position.x - a , m_position.y), m_scale);
	if (t <= 1.0f)
	{
		TexRender(m_tenTexture, m_tenTexCenter, m_position, m_scale);
	}
	OneNumberRender(m_secFirstDigit, Vector2(m_position.x + a , m_position.y), m_scale);
	OneNumberRender(m_secSecondDigit, Vector2(m_position.x + a * 2, m_position.y), m_scale);


}

void Timer::PlaySceneRender(DirectX::SimpleMath::Vector2 Pos, float Scale)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//�����̊Ԋu
	int a = 30;

	float gameTime = m_commonResources->GetStepTimer()->GetTotalSeconds();
	//2�b�𒴂�����0�ɖ߂�
	float t = fmodf(gameTime, 2.0f);


	OneNumberRender(m_minFirstDigit, Vector2(Pos.x - a * 2, Pos.y), Scale);
	OneNumberRender(m_minSecondDigit, Vector2(Pos.x - a, Pos.y), Scale);
	if (t <= 1.0f)
	{
		TexRender(m_tenTexture, m_tenTexCenter, Pos, Scale);
	}
	OneNumberRender(m_secFirstDigit, Vector2(Pos.x + a, Pos.y), Scale);
	OneNumberRender(m_secSecondDigit, Vector2(Pos.x + a * 2, Pos.y),Scale);


}


void Timer::CreateNumberTex(const wchar_t* szFileName,Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex, DirectX::SimpleMath::Vector2& texCenter)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

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
		

		// �P�̔ԍ��̒��S���W
		texCenter = Vector2(m_width,m_height) ;

}

void Timer::OneNumberRender(int number,DirectX::SimpleMath::Vector2 Pos, float Scale)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto states = m_commonResources->GetCommonStates();

	// �X�v���C�g�o�b�`�̊J�n�F�I�v�V�����Ń\�[�g���[�h�A�u�����h�X�e�[�g���w�肷��
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	//���̔ԍ����Ƃ̕��ƍ������K�v
	float Width = 120;   //��
	float Hight = 142;   //����

	RECT NumberRECT{ 0 + number * Width, 1,
			110 + number * Width, Hight };

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

void Timer::TexRender(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Tex, DirectX::SimpleMath::Vector2& Center, DirectX::SimpleMath::Vector2 Pos, float Scale)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	auto states = m_commonResources->GetCommonStates();


	// �X�v���C�g�o�b�`�̊J�n�F�I�v�V�����Ń\�[�g���[�h�A�u�����h�X�e�[�g���w�肷��
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	// Title��`�悷��
	m_spriteBatch->Draw(
		Tex.Get(),	// �e�N�X�`��(SRV)
		Pos,				// �X�N���[���̕\���ʒu(origin�̕`��ʒu)
		nullptr,			// ��`(RECT)
		Colors::White,		// �w�i�F
		0.0f,				// ��]�p(���W�A��)
		Center,		// �e�N�X�`���̊�ɂȂ�\���ʒu(�`�撆�S)(origin)
		Scale,				// �X�P�[��(scale)
		SpriteEffects_None,	// �G�t�F�N�g(effects)
		0.0f				// ���C���[�x(�摜�̃\�[�g�ŕK�v)(layerDepth)
	);


	// �X�v���C�g�o�b�`�̏I���
	m_spriteBatch->End();

}


void Timer::CreateTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex, DirectX::SimpleMath::Vector2& texCenter)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();


	// �摜�����[�h����
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			szFileName,
			nullptr,
			tex.ReleaseAndGetAddressOf()
		)
	);


	/*
		�ȉ��A�e�N�X�`���̑傫�������߂遨�e�N�X�`���̒��S���W���v�Z����
	*/
	// �ꎞ�I�ȕϐ��̐錾
	Microsoft::WRL::ComPtr<ID3D11Resource> resource{};
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2D{};
	D3D11_TEXTURE2D_DESC desc{};
	Vector2 texSize{};

	// �e�N�X�`���̏����擾����================================
	// �e�N�X�`����ID3D11Resource�Ƃ��Č���
	tex->GetResource(resource.GetAddressOf());

	// ID3D11Resource��ID3D11Texture2D�Ƃ��Č���
	resource.As(&tex2D);

	// �e�N�X�`�������擾����
	tex2D->GetDesc(&desc);

	// �e�N�X�`���T�C�Y���擾���Afloat�^�ɕϊ�����
	texSize.x = static_cast<float>(desc.Width);
	texSize.y = static_cast<float>(desc.Height);

	// �e�N�X�`���̒��S�ʒu���v�Z����
	texCenter = texSize / 2.0f;

}

/// <summary>
/// titalTime���玞�Ԃ����߂�
/// </summary>
void Timer::TimeCalculation()
{
	int time = m_totalTime;
	int min = (time % 3600) / 60;
	int sec = time % 60;

	m_minFirstDigit = min / 10;
	m_minSecondDigit = min % 10;
	m_secFirstDigit = sec / 10;
	m_secSecondDigit = sec % 10;
}
