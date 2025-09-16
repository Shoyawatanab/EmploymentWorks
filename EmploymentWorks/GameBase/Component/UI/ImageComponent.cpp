/*
	�N���X��     : ImageComponent
	����         : �摜UI�R���|�[�l���g
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "ImageComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/GameResources.h"
#include "Libraries/MyLib/BinaryFile.h"
#include "GameBase/Screen.h"
#include "GameBase/Component/Transform/Transform.h"
#include "GameBase/UI/Canvas/Canvas.h"



/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="textureName">�摜��</param>
ImageComponent::ImageComponent(Canvas* canvas, Actor* owner, std::string textureName)
	:
	Component(owner)
	,m_texture{}

	,m_textureHeight{}
	,m_textureWidth{}
	,m_color{DirectX::SimpleMath::Vector4(1.0f,1.0f,1.0f,1.0f)}
	,m_cutRange{DirectX::SimpleMath::Vector4(0.0f,0.0f,1.0f,1.0f)}
	,m_viewRange{DirectX::SimpleMath::Vector4::One}
	,m_fillAmount{DirectX::SimpleMath::Vector4::One}
	,m_renderKinds{RenderKinds::NORMAL}
	,m_angle{}
{

	using namespace DirectX;


	//�L�����o�X�ɒǉ�
	canvas->AddImageComponent(this);

	LoadTexture(textureName);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ImageComponent::~ImageComponent()
{
}




/// <summary>
/// �摜�̓ǂݍ���
/// </summary>
/// <param name="textureName"></param>
void ImageComponent::LoadTexture(std::string textureName)
{

	//�摜�̓ǂݍ���
	m_texture = GameResources::GetInstance()->GetTexture(textureName);

	//�V�F�[�_�[���\�[�X�r���[����摜���̎擾
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	m_texture->GetResource(&resource);

	//���\�[�X��Texture2D�ɃL���X�g
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(resource.As(&tex));

	//�摜�����擾
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	//�摜�̃T�C�Y���擾
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;

}


/// <summary>
/// �����̎擾
/// </summary>
/// <returns></returns>
float ImageComponent::GetWidth() const
{
	return m_textureWidth * GetActor()->GetTransform()->GetWorldScale().x;
}

/// <summary>
/// �c���̎擾
/// </summary>
/// <returns></returns>
float ImageComponent::GetHeight() const
{
	return m_textureHeight * GetActor()->GetTransform()->GetWorldScale().y;
}



/// <summary>
/// �J�X�^���`��֐��̓o�^
/// </summary>
/// <param name="customRender">�֐�</param>
void ImageComponent::SetCustomRenderFunction(std::function<void()> customRender)
{

	m_customRender = customRender;
	//��Ԃ̕ύX
	m_renderKinds = RenderKinds::CUSTOM;
}
