/*
	クラス名     : ImageComponent
	説明         : 画像UIコンポーネント
	補足・注意点 :
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
/// コンストラク
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="textureName">画像名</param>
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


	//キャンバスに追加
	canvas->AddImageComponent(this);

	LoadTexture(textureName);

}

/// <summary>
/// デストラクタ
/// </summary>
ImageComponent::~ImageComponent()
{
}




/// <summary>
/// 画像の読み込み
/// </summary>
/// <param name="textureName"></param>
void ImageComponent::LoadTexture(std::string textureName)
{

	//画像の読み込み
	m_texture = GameResources::GetInstance()->GetTexture(textureName);

	//シェーダーリソースビューから画像情報の取得
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	m_texture->GetResource(&resource);

	//リソースをTexture2Dにキャスト
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(resource.As(&tex));

	//画像情報を取得
	D3D11_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	//画像のサイズを取得
	m_textureWidth = desc.Width;
	m_textureHeight = desc.Height;

}


/// <summary>
/// 横幅の取得
/// </summary>
/// <returns></returns>
float ImageComponent::GetWidth() const
{
	return m_textureWidth * GetActor()->GetTransform()->GetWorldScale().x;
}

/// <summary>
/// 縦幅の取得
/// </summary>
/// <returns></returns>
float ImageComponent::GetHeight() const
{
	return m_textureHeight * GetActor()->GetTransform()->GetWorldScale().y;
}



/// <summary>
/// カスタム描画関数の登録
/// </summary>
/// <param name="customRender">関数</param>
void ImageComponent::SetCustomRenderFunction(std::function<void()> customRender)
{

	m_customRender = customRender;
	//状態の変更
	m_renderKinds = RenderKinds::CUSTOM;
}
