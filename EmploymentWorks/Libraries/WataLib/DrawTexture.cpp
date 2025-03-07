/*
	@file	DrawTexture.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "DrawTexture.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>


#include "Libraries/MyLib/DebugString.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �R���X�g���N�^
//---------------------------------------------------------
WataLib::DrawTexture::DrawTexture()
	:
	m_commonResources{},
	m_spriteBatch{},
	m_spriteFont{},
	m_texture{},
	m_texCenter{},
	m_position{},
	m_scale{},
	m_rotate{}
	,m_expansion{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
WataLib::DrawTexture::~DrawTexture()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void WataLib::DrawTexture::Initialize(CommonResources* resources, const wchar_t* szFileName, DirectX::SimpleMath::Vector2 Pos, DirectX::SimpleMath::Vector2 scale)
{
	assert(resources);
	m_commonResources = resources;
	m_position = Pos;
	m_scale = scale;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();


	// �X�v���C�g�o�b�`���쐬����
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	// �X�v���C�g�t�H���g���쐬����
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(
		device,
		L"Resources/Fonts/SegoeUI_18.spritefont"
	);


	// �摜�����[�h����
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			szFileName,
			nullptr,
			m_texture.ReleaseAndGetAddressOf()
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
	m_texture->GetResource(resource.GetAddressOf());

	// ID3D11Resource��ID3D11DrawTexture2D�Ƃ��Č���
	resource.As(&tex2D);

	// �e�N�X�`�������擾����
	tex2D->GetDesc(&desc);

	// �e�N�X�`���T�C�Y���擾���Afloat�^�ɕϊ�����
	texSize.x = static_cast<float>(desc.Width);
	texSize.y = static_cast<float>(desc.Height);

	// �e�N�X�`���̒��S�ʒu���v�Z����
	m_texCenter = texSize / 2.0f;

	m_expansion = 1.0f;

}


//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void WataLib::DrawTexture::Render()
{

	auto states = m_commonResources->GetCommonStates();

	float a  =1.0f;

	DirectX::XMVECTORF32 color = Colors::White;
	color.f[0] *= a;
	color.f[1] *= a;
	color.f[2] *= a;

	// �X�v���C�g�o�b�`�̊J�n�F�I�v�V�����Ń\�[�g���[�h�A�u�����h�X�e�[�g���w�肷��
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	// Title��`�悷��
	m_spriteBatch->Draw(
		m_texture.Get(),	// �e�N�X�`��(SRV)
		m_position,				// �X�N���[���̕\���ʒu(origin�̕`��ʒu)
		nullptr,			// ��`(RECT)
		color,		// �w�i�F
		m_rotate,				// ��]�p(���W�A��)
		m_texCenter,		// �e�N�X�`���̊�ɂȂ�\���ʒu(�`�撆�S)(origin)
		m_scale * m_expansion,				// �X�P�[��(scale)
		SpriteEffects_None,	// �G�t�F�N�g(effects)
		0.0f				// ���C���[�x(�摜�̃\�[�g�ŕK�v)(layerDepth)
	);



	// �X�v���C�g�o�b�`�̏I���
	m_spriteBatch->End();



}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void WataLib::DrawTexture::Finalize()
{
	// do nothing.
}


