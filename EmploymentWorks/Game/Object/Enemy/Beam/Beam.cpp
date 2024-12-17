/*
	@file	Beam.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Beam.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Object/Enemy/Beam/BeamRays.h"
#include "Game/Object/Enemy/Beam/BeamEnergyBall.h"
#include "Game/Object/Enemy/Beam/BeamChargeEffect.h"

#include "Game/DetectionCollision/CollisionManager.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;



const std::vector<D3D11_INPUT_ELEMENT_DESC> Beam::INPUT_LAYOUT =
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
Beam::Beam()
	:
	m_commonResources{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Beam::~Beam()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Beam::Initialize()
{

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	//BinaryFile VS = BinaryFile::LoadFile(L"Resources/Shaders/BeamVS.cso");
	//BinaryFile PS = BinaryFile::LoadFile(L"Resources/Shaders/BeamPS.cso");


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




	m_position = Vector3::Zero;

	//ビームの太さ
	m_thickness = 0.9f;

	m_initialScale = Vector3(m_thickness, m_thickness, 0.0f);

	m_scale = m_initialScale;

	m_rotate = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(0.0f));

	m_target = Vector3(0, 0, 5);


	m_isHit = false;

	m_maxLength = 0.3f;

	float scale = 2.0f;

	m_chargyBallParamater->InitialScale = Vector3::Zero;

	m_chargyBallParamater->MaxScale = Vector3(1.0f, 1.0f, 1.0f) * scale;
	//予備動作の時間
	m_chargyBallParamater->MaxPreliminaryActionTime = 2.0f;
	//エネルギー弾の溜め時間
	m_chargyBallParamater->AccumulationTime = 2.0f;

	m_chargyBallParamater->ChargeEffectCreateTime = 0.5f;

	m_chargyBallParamater->ShrinkTime = 0.6f;

	m_chargyBallParamater->MoveSpeed = 20.0f;


	m_raysParameter->InitialScale = Vector3(0.0f,0.0f,0.0f);

	m_raysParameter->MaxScale = Vector3(1.0, 1.0f, 0.0f) * scale;

	m_raysParameter->MoveSpeed = 1.0f;

	m_raysParameter->ShrinkTime = 0.6f;

	m_idling->Initialize();
	m_attack->Initialize();
	m_attackEnd->Initialize();
	m_preliminaryAction->Initialize();

	m_energyBall->Initialize();
	m_rays->Initialize();


	m_currentState = m_idling.get();

	m_isHit = false;

	m_classState = CurrentClassState::Idling;

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Beam::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	m_currentState->Update(elapsedTime);

	//for (auto& particle : m_chargeEffect)
	//{
	//	particle->Update(elapsedTime);


	//}

		//敵の現在の座標の取得
	Vector3 startPosition = m_position;
	//プレイヤの現在の座標の取得
	Vector3 endPosition = m_target;
	//敵からプレイヤの方向ベクトルの計算
	Vector3 toPlayer = endPosition - startPosition;
	//yawの計算　（左右回転）
	//xz平面で敵からプレイヤの方向を求める
	float yaw = atan2(toPlayer.x, toPlayer.z);
	//pitchの計算（上下回転）
	//敵からプレイヤのウ違勅方向を求める
	float pitch = atan2(toPlayer.y, sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z));

	//yaw pitchから回転を計算 pitchは反転させる
	m_rotate = Quaternion::CreateFromYawPitchRoll(yaw, -pitch, 0.0f);


	


	for (auto& effect : m_deleteChargeEffect)
	{
		m_chargeEffect.erase(
			std::remove_if(
				m_chargeEffect.begin(), m_chargeEffect.end(),
				[&effect](const std::unique_ptr<BeamChargeEffect>& particle) {
					return particle.get() == effect; // 一致するかを判定
				}
			),
			m_chargeEffect.end()
		);
	}

	m_deleteChargeEffect.clear();


	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.E)
	{
		ChangeState(m_attackEnd.get());
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Beam::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();




	switch (m_classState)
	{
		case Beam::Idling:
			break;
		case Beam::PreliminaryAction:
			m_energyBall->Render(view, projection);
			for (auto& partcle : m_chargeEffect)
			{
				partcle->Render(view, projection);
			}
			break;
		case Beam::Attack:
			m_energyBall->Render(view, projection);
			m_rays->Render(view, projection);

			break;
		case Beam::AttackEnd:
			m_energyBall->Render(view, projection);
			m_rays->Render(view, projection);

			break;
		default:
			break;
	}
	

	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Beam::Finalize()
{
	// do nothing.
}

void Beam::RegistrationInformation(CommonResources* resources)
{

	m_commonResources = resources;

	m_idling->RegistrationInformation(m_commonResources, this);
	m_attack->RegistrationInformation(m_commonResources, this);
	m_attackEnd->RegistrationInformation(m_commonResources, this);
	m_preliminaryAction->RegistrationInformation(m_commonResources, this);
	m_energyBall->RegistrationInformation(m_commonResources, this);
	m_rays->RegistrationInformation(m_commonResources, this);


}

void Beam::Instances()
{

	m_idling = std::make_unique<Beamldling>();
	m_attack = std::make_unique<BeamAttack>();
	m_attackEnd = std::make_unique<BeamAttackEnd>();
	m_preliminaryAction = std::make_unique<BeamPreliminaryAction>();
	m_energyBall = std::make_unique<BeamEnergyBall>();
	m_rays = std::make_unique<BeamRays>();

	m_chargyBallParamater = std::make_unique<Beam::ChargyBallParamater>();

	m_raysParameter = std::make_unique<RaysParameter>();




}

void Beam::RegistrationCollionManager(CollisionManager* collsionManager)
{

	m_energyBall->RegistrationCollionManager(collsionManager);

}

void Beam::ChangeState(IBeamState* nextState)
{
	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}

void Beam::CreateParticle()
{

	std::vector<Vector3> position;
	std::vector<Quaternion> rotate;


	float radius = 0.9f;

	for (int angle = 0; angle < 360; angle += 45)
	{
		// 角度をラジアンに変換   スタートを上から始めるために９０度プラスする　９０足さないと右から始まる
		float radian = DirectX::XMConvertToRadians(angle) + DirectX::XMConvertToRadians(90);

		// 座標を計算（上から反時計回りにする）
		float x = radius * cos(radian); // X座標
		float y = radius * sin(radian); // Y座標

		// 座標を追加
		position.push_back(Vector3(x, y, 0.0f));

		// 回転を追加（座標と同じ基準で回転を作成）
		rotate.push_back(Quaternion::CreateFromAxisAngle(Vector3::UnitZ, DirectX::XMConvertToRadians(angle)));

	}


	for (int i = 0; i < position.size(); i++)
	{
		auto particle = std::make_unique<BeamChargeEffect>();
		particle->RegistrationInformation(m_commonResources, this);
		particle->Initialize(position[i], rotate[i]);

		m_chargeEffect.push_back(std::move(particle));

	}
}

void Beam::RegistrationDeleteParticle(BeamChargeEffect* effect)
{
	m_deleteChargeEffect.push_back(effect);

}

void Beam::DeleteParticle()
{

	m_chargeEffect.clear();

}


