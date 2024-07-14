/*
	@file	TitleScene.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "TitleScene.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>


#include "Libraries/MyLib/DebugString.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_commonResources{},
	m_spriteBatch{},
	m_spriteFont{},
	m_texture{},
	m_texCenter{},
	m_isChangeScene{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TitleScene::~TitleScene()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TitleScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();


	// �X�v���C�g�o�b�`���쐬����
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	// �X�v���C�g�t�H���g���쐬����
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(
		device,
		L"Resources/Fonts/SegoeUI_18.spritefont"
	);


	CreateTex(L"Resources/Textures/Title.png", m_texture[0], m_texCenter[0]);
	CreateTex(L"Resources/Textures/pushSpace.png", m_texture[1], m_texCenter[1]);

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
	m_titleScale = 0.4f;
	m_isTitleScale = false;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
{
	// �錾���������A���ۂ͎g�p���Ă��Ȃ��ϐ�
	UNREFERENCED_PARAMETER(elapsedTime);

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	UpdateScale(m_titleScale,0.002f,0.3f,0.4f,m_isTitleScale);

	// �X�y�[�X�L�[�������ꂽ��
	if (kbTracker->released.Space)
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleScene::Render()
{

	auto states = m_commonResources->GetCommonStates();


	// �X�v���C�g�o�b�`�̊J�n�F�I�v�V�����Ń\�[�g���[�h�A�u�����h�X�e�[�g���w�肷��
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	// TRIDENT���S�̕`��ʒu�����߂�
	RECT rect{ m_commonResources->GetDeviceResources()->GetOutputSize() };
	// �摜�̒��S���v�Z����
	Vector2 pos{ rect.right / 2.0f, rect.bottom / 2.0f };


	// Title��`�悷��
	m_spriteBatch->Draw(
		m_texture[0].Get(),	// �e�N�X�`��(SRV)
		pos + Vector2(0,-100),				// �X�N���[���̕\���ʒu(origin�̕`��ʒu)
		nullptr,			// ��`(RECT)
		Colors::White,		// �w�i�F
		0.0f,				// ��]�p(���W�A��)
		m_texCenter[0],		// �e�N�X�`���̊�ɂȂ�\���ʒu(�`�撆�S)(origin)
		m_titleScale,				// �X�P�[��(scale)
		SpriteEffects_None,	// �G�t�F�N�g(effects)
		0.0f				// ���C���[�x(�摜�̃\�[�g�ŕK�v)(layerDepth)
	);

	//PushSpace�̕`��
	m_spriteBatch->Draw(
		m_texture[1].Get(),	// �e�N�X�`��(SRV)
		pos + Vector2(0,150),				// �X�N���[���̕\���ʒu(origin�̕`��ʒu)
		nullptr,			// ��`(RECT)
		Colors::White,		// �w�i�F
		0.0f,				// ��]�p(���W�A��)
		m_texCenter[1],		// �e�N�X�`���̊�ɂȂ�\���ʒu(�`�撆�S)(origin)
		0.3f,				// �X�P�[��(scale)
		SpriteEffects_None,	// �G�t�F�N�g(effects)
		0.0f				// ���C���[�x(�摜�̃\�[�g�ŕK�v)(layerDepth)
	);

	// �X�v���C�g�o�b�`�̏I���
	m_spriteBatch->End();


	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Title Scene");

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TitleScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID TitleScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::PLAY;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}

void TitleScene::CreateTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex, DirectX::SimpleMath::Vector2& texCenter)
{
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
/// Scale�̒l���J��Ԃ���������֐�
/// </summary>
/// <param name="scale">�傫���̕ϐ�</param>
/// <param name="increment">���Z�l</param>
/// <param name="min">�ŏ��l</param>
/// <param name="max">�ő�l</param>
/// <param name="increasing">bool�ϐ�</param>
void TitleScene::UpdateScale(float& scale, float increment, float min, float max, bool& increasing) {
	if (increasing) {
		scale += increment;
		// max�l�𒴂����ꍇ�Ɍ����ɓ]����
		if (scale >= max) {
			scale = max;
			increasing = false;
		}
	}
	else {
		scale -= increment;
		// min�l����������ꍇ�ɑ����ɓ]����
		if (scale <= min) {
			scale = min;
			increasing = true;
		}
	}
}


