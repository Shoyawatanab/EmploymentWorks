#include "pch.h"
#include "Model3D.h"

#include "Game/CommonResources.h"
#include "DeviceResources.h"

//	名前空間の使用
using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
WataLib::Model3D::Model3D()
	:
	m_commonResources{},
	m_scale{}
{
}

/// <summary>
/// 開始関数
/// </summary>
/// <param name="pDeviceContext">デバイスコンテキストのポインタ</param>
/// <param name="pCommonStatesm">共通ステートのポインタ</param>
/// <param name="modelHandle">モデルハンドル</param>
void WataLib::Model3D::Initialize
(
	CommonResources* resouce, const wchar_t* szFileName, DirectX::SimpleMath::Vector3 Pos, DirectX::SimpleMath::Vector3 Scale
)
{

	m_commonResources = resouce;
	m_position = Pos;
	m_scale = Scale;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();


	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device,szFileName, *fx);


}

/// <summary>
/// 描画関数
/// </summary>
/// <param name="camera">カメラ</param>
void WataLib::Model3D::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	//	ワールド行列の作成
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateScale			(m_scale);		//	スケール
	world *= SimpleMath::Matrix::CreateFromQuaternion	(m_rotate);		//	回転
	world *= SimpleMath::Matrix::CreateTranslation		(m_position);	//	座標

	m_model->Draw(context, *states, world, view, projection);

}
