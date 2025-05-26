/*
	@file	Barrier.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Barrier.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/WataLib/GameResources.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/Params.h"
#include "Game/Observer/Messenger.h"
#include "Game/Enemys/BossEnemy/Barrier/State/BarrierStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



const std::vector<D3D11_INPUT_ELEMENT_DESC> Barrier::INPUT_LAYOUT =
{
	{ "POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="parent">親</param>
Barrier::Barrier(CommonResources* resources, BaseEntity* parent)
	:
	MoveEntity(resources,Vector3::Zero,Vector3::Zero,Quaternion::Identity)
	,m_model{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_inputLayout{}
	,m_CBuffer{}
	,m_initialScale{}
	,m_initialRotate{}
	,m_maxScale{}
	,m_maxSizeTime{}
	,m_time{}
	,m_stateMachine{}
{
	BaseEntity::SetParent(parent);
	BaseEntity::SetIsEntityActive(false);
	m_stateMachine = std::make_unique<BarrierStateMachine>(BaseEntity::GetCommonResources(),this);
}

/// <summary>
/// デストラクタ
/// </summary>
Barrier::~Barrier()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void Barrier::Initialize()
{

	MoveEntity::Initialize();

	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();


	BinaryFile VS = BinaryFile::LoadFile(L"Resources/Shaders/BarrierVS.cso");
	BinaryFile PS = BinaryFile::LoadFile(L"Resources/Shaders/BarrierPS.cso");


	//	インプットレイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		VS.GetData(), VS.GetSize(),
		m_inputLayout.ReleaseAndGetAddressOf());


	DX::ThrowIfFailed(
		device->CreateVertexShader(
			VS.GetData(),
			VS.GetSize(),
			nullptr,
			m_vertexShader.ReleaseAndGetAddressOf())
	);


	DX::ThrowIfFailed(
		device->CreatePixelShader(
			PS.GetData(),
			PS.GetSize(),
			nullptr,
			m_pixelShader.ReleaseAndGetAddressOf())
	);

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	device->CreateBuffer(&bd, nullptr, &m_CBuffer);

	// モデルを読み込む
	m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("Barrier");

	//BaseEntity::SetLocalScale(SCALE);

	m_maxScale = Params::BOSSENEMY_BEAM_BALL_MAX_SCALE;

	m_initialRotate = Quaternion::Identity;


	//何秒で最大サイズになるか
	m_maxSizeTime =Params::BOSSENEMY_BEAM_BALL_ACCUMULATIONTIME ;

	m_time = 0;


	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), Params::BOSSENEMY_BEAM_BALL_SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Params::BOSSENEMY_BEAM_BALL_BOX_COLLIDER_SIZE);

	m_stateMachine->Initialize(BaseEntity::GetCommonResources());

}


/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void Barrier::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//オブジェクトか描画が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}

	MoveEntity::Render(view, projection);


	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	Vector4 color = Vector4(1, 1, 1, 0.5f);

	//モデルを描画する
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection, false, [&]()
		{

			ConstBuffer cbuff;
			cbuff.matWorld = BaseEntity::GetWorldMatrix().Transpose();

			cbuff.matView = view.Transpose();
			cbuff.matProj = projection.Transpose();
			cbuff.Color = color;

			context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

			ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
			context->VSSetConstantBuffers(0, 1, cb);
			context->PSSetConstantBuffers(0, 1, cb);

			context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

			////	深度バッファに書き込み参照する
			context->OMSetDepthStencilState(states->DepthDefault(), 0);

			////	カリングはなし
			context->RSSetState(states->CullCounterClockwise());


			context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_pixelShader.Get(), nullptr, 0);


			context->IASetInputLayout(m_inputLayout.Get());
		});



	//当たり判定の描画
	CollisionEntity::GetBounding()->DrawBoundingSphere(BaseEntity::GetPosition(), view, projection);
	CollisionEntity::GetBounding()->DrawBoundingBox(BaseEntity::GetPosition(), view, projection);




}


/// <summary>
/// 当たり判定クラスに追加
/// </summary>
/// <param name="collsionManager">当たり判定クラス</param>
void Barrier::AddCollision(CollisionManager* collsionManager)
{

	CollisionEntity::AddCollision(collsionManager);
}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void Barrier::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::BOOMERANG:
			break;
		default:
			break;
	}

}


/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Barrier::Update(const float& elapsedTime)
{
	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	MoveEntity::Update(elapsedTime);

	m_stateMachine->Update(elapsedTime);

	m_time += elapsedTime;

}

/// <summary>
/// 有効になったら
/// </summary>
void Barrier::OnEnable()
{

	m_stateMachine->ChangeState(m_stateMachine->GetBarrierGenerare());

}

/// <summary>
/// 無効になったら
/// </summary>
void Barrier::OnDisable()
{
}


/// <summary>
/// リセット
/// </summary>
void Barrier::ReSet()
{
	m_time = 0;
}



