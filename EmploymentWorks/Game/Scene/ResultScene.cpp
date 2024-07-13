/*
	@file	ResultScene.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "ResultScene.h"
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
ResultScene::ResultScene()
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
ResultScene::~ResultScene()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void ResultScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// �X�v���C�g�o�b�`���쐬����
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);


	CreateTex(L"Resources/Textures/Number.png", m_texture, m_texCenter);

	//for (int i = 0; i < 10 ; i++)
	//{
	//	m_numberTexture.emplace_back();
	//	m_numberTexCenter.emplace_back();

	//	CreateTex(L"Resources/Textures/Number.png",m_numberTexture[i], m_numberTexCenter[i]);
	//}


	// �V�[���ύX�t���O������������
	m_isChangeScene = false;

	num = 0;

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void ResultScene::Update(float elapsedTime)
{
	// �錾���������A���ۂ͎g�p���Ă��Ȃ��ϐ�
	UNREFERENCED_PARAMETER(elapsedTime);

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	// �X�y�[�X�L�[�������ꂽ��
	if (kbTracker->released.Space)
	{
		m_isChangeScene = true;
	}


	if (kbTracker->released.O && num < 9)
	{
		num++;
	}
	if (kbTracker->released.I && num > 0)
	{
		num--;
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void ResultScene::Render()
{


	m_commonResources->GetTimer()->Render();

	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Result Scene");

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void ResultScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID ResultScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::TITLE;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}




void ResultScene::CreateTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex, DirectX::SimpleMath::Vector2& texCenter)
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


void ResultScene::CreateNumberTex(const wchar_t* szFileName, std::vector< Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>& tex, std::vector<DirectX::SimpleMath::Vector2>& texCenter)
{

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Tex;

	//�ԍ��̉摜�̓ǂݍ���
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			szFileName,
			nullptr,
			Tex.ReleaseAndGetAddressOf()
		)
	);

	
	

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> NumberTex;
	DirectX::SimpleMath::Vector2 NumberTexCenter;


}


