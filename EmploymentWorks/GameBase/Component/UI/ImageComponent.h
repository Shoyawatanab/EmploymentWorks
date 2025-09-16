/*
	クラス名     : ImageComponent
	説明         : 画像UIコンポーネント
	補足・注意点 :
*/
#pragma once
#include "GameBase/Component.h"

class Canvas;


class ImageComponent : public Component
{

public:	




	//描画種類
	enum class RenderKinds
	{
		NORMAL    //通常
		,CUSTOM	  //カスタム
	};

public:

	//画像の取得
	ID3D11ShaderResourceView* GetImage() { return m_texture.Get(); }

	//切り取り範囲のセット
	void SetCutRange(DirectX::SimpleMath::Vector4 range) { m_cutRange = range; }
	//切り取り範囲の取得
	DirectX::SimpleMath::Vector4 const GetCutRange() { return m_cutRange; }
	//色のセット
	void SetColor(DirectX::SimpleMath::Vector4 color) { m_color = color; }
	//色の取得
	DirectX::SimpleMath::Vector4 const GetColor() { return m_color; }

	//横の塗りつぶし量　０～１までの範囲
	void SetHorizontalFillAmount(float fillAmount) { m_fillAmount.x = fillAmount; }
	//塗りつぶし量の取得
	DirectX::SimpleMath::Vector4 const GetFillAmount() { return m_fillAmount; }
	
	//表示範囲のセット
	void SetViewRange(DirectX::SimpleMath::Vector2 range) { m_viewRange.x = range.x; m_viewRange.y = range.y; }
	//表示範囲の取得
	DirectX::SimpleMath::Vector4 const GetViewRange() { return m_viewRange; }

	//横幅の取得
	float GetWidth() const;
	//縦幅の取得
	float GetHeight() const;
	//カスタム描画関数の登録
	void SetCustomRenderFunction(std::function<void()> customRender);
	//回転のセット
	void SetAngle(const float& angle) { m_angle = angle; }
	//回転の取得
	float GetAngle() const { return m_angle; }
	//描画種類の取得
	RenderKinds GetRenderKinds() { return m_renderKinds; }
	//画像の取得
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture() { return m_texture; }
	//カスタム描画関数の取得
	std::function<void()> GetCustomRenderFunction() { return m_customRender; }

	int const GetTextureWidth() { return m_textureWidth; }
	int const GetTextureHeight() { return m_textureHeight; }

public:
	//コンストラクタ
	ImageComponent(Canvas* canvas,Actor* owner,std::string textureName);
	//デストラクタ
	~ImageComponent() override;


private:

	//画像の読み込み
	void LoadTexture(std::string textureName);

private:

	//画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;




	//画像の大きさ
	int m_textureWidth;
	int	m_textureHeight;
	//色
	DirectX::SimpleMath::Vector4 m_color;
	//切り取り範囲
	DirectX::SimpleMath::Vector4 m_cutRange;
	//塗りつぶし量　x: 横　y :縦
	DirectX::SimpleMath::Vector4 m_fillAmount;
	//表示範囲
	DirectX::SimpleMath::Vector4 m_viewRange;

	//描画の種類
	RenderKinds m_renderKinds;

	//個別描画
	std::function<void()> m_customRender;
	//回転
	float m_angle;

};