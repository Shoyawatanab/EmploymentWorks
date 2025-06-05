#pragma once
#include "GameBase/Actor.h"

class Canvas;

class UserInterface2 : public Actor
{
public:
	//コンストラクタ
	UserInterface2(Canvas* canvas,std::string textureName);
	//デストラクタ
	~UserInterface2();


private:

	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;


};