/*
	@file	BeamEnergyBall.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BeamEnergyBall.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Object/Enemy/Beam/Beam.h"
#include "Libraries/MyLib/Bounding.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



const std::vector<D3D11_INPUT_ELEMENT_DESC> BeamEnergyBall::INPUT_LAYOUT =
{
	{ "POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
BeamEnergyBall::BeamEnergyBall()
	:
	m_commonResources{},
	m_model{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
BeamEnergyBall::~BeamEnergyBall()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void BeamEnergyBall::Initialize()
{

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	//BinaryFile VS = BinaryFile::LoadFile(L"Resources/Shaders/BeamEnergyBallVS.cso");
	//BinaryFile PS = BinaryFile::LoadFile(L"Resources/Shaders/BeamEnergyBallPS.cso");


	////	インプットレイアウトの作成
	//device->CreateInputLayout(&INPUT_LAYOUT[0],
	//	static_cast<UINT>(INPUT_LAYOUT.size()),
	//	VS.GetData(), VS.GetSize(),
	//	m_inputLayout.ReleaseAndGetAddressOf());


	//DX::ThrowIfFailed(
	//	device->CreateVertexShader(
	//		VS.GetData(),
	//		VS.GetSize(),
	//		nullptr,
	//		m_vertexShader.ReleaseAndGetAddressOf())
	//);


	//DX::ThrowIfFailed(
	//	device->CreatePixelShader(
	//		PS.GetData(),
	//		PS.GetSize(),
	//		nullptr,
	//		m_pixelShader.ReleaseAndGetAddressOf())
	//);

	////	シェーダーにデータを渡すためのコンスタントバッファ生成
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(ConstBuffer);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;

	//device->CreateBuffer(&bd, nullptr, &m_CBuffer);



	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BeamEnergyBall.cmo", *fx);

	m_position = Vector3::Zero;

	Beam::ChargyBallParamater* paramater = m_beam->GetBeamParamater();


	m_initialScale = paramater->InitialScale;

	m_scale = m_initialScale;
	;

	m_maxScale = paramater->MaxScale;

	m_initialRotate = Quaternion::Identity;

	m_target = Vector3(0, 0, 5);

	//何秒で最大サイズになるか
	m_maxSizeTime = paramater->AccumulationTime;

	m_time = 0;

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 4.0f);
	m_bounding->CreateBoundingBox(m_commonResources, m_position,  Vector3(1.5f,1.5f,1.5f));


}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void BeamEnergyBall::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void BeamEnergyBall::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	m_rotate = m_initialRotate;



	// ワールド行列を更新する
	Matrix world = Matrix::Identity;
	world *= Matrix::CreateScale(m_scale);
	world *= Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);
	world *= Matrix::CreateFromQuaternion(m_beam->GetRotate());
	world *= Matrix::CreateTranslation(m_beam->GetPosition());

	//モデルを描画する
	m_model->Draw(context, *states, world, view, projection, false, [&]()
		{

			//ConstBuffer cbuff;
			//cbuff.matWorld = world.Transpose();

			//cbuff.matView = view.Transpose();
			//cbuff.matProj = projection.Transpose();

			//context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

			//ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
			//context->VSSetConstantBuffers(0, 1, cb);
			//context->PSSetConstantBuffers(0, 1, cb);

			//context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

			//////	深度バッファに書き込み参照する
			//context->OMSetDepthStencilState(states->DepthDefault(), 0);

			//////	カリングはなし
			//context->RSSetState(states->CullNone());


			//context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
			//context->PSSetShader(m_pixelShader.Get(), nullptr, 0);


			//context->IASetInputLayout(m_inputLayout.Get());

		});


	//UPdateでやると動かない
	m_bounding->Update(Vector3::Transform(Vector3::Zero,world));

	m_bounding->DrawBoundingBox(view, projection);
	m_bounding->DrawBoundingSphere(view, projection);


	//context->VSSetShader(nullptr, nullptr, 0);
	//context->PSSetShader(nullptr, nullptr, 0);

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void BeamEnergyBall::Finalize()
{
	// do nothing.
}

void BeamEnergyBall::RegistrationInformation(CommonResources* resoure, Beam* beam)
{

	m_commonResources = resoure;

	m_beam = beam;



}

void BeamEnergyBall::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}

void BeamEnergyBall::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{

	if (m_beam->GetCurrentState() != m_beam->GetBeamAttack())
	{
		return;
	}

	m_beam->ChangeState(m_beam->GetBeamAttackEnd());

}


