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



//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Timer::Timer()
	:
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

	//���̔ԍ����Ƃ̕��ƍ������K�v
	m_width = 120;   //��
	m_height = 142;   //����

	m_totalTime = 0;
	m_scale = 0.3f;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Timer::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);


	m_totalTime += elapsedTime;

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Timer::Render()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	int a = 35;

	OneNumberRender(1, Vector2(100 + a, 100),m_scale);
	OneNumberRender(2, Vector2(100 + a * 2, 100), m_scale);
	OneNumberRender(3, Vector2(100 + a * 3, 100), m_scale);
	OneNumberRender(4, Vector2(100 + a * 4, 100), m_scale);


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

