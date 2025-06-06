/*
	@file	BirdEnemyBeamEnergyBall.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BirdEnemyBeamEnergyBall.h"
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
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Libraries/WataLib/Bounding.h"
#include "GameBase/Manager/CollisiionManager.h"
#include "Game/Observer/Messenger.h"

#include "Game/Params.h"


const std::vector<D3D11_INPUT_ELEMENT_DESC> BirdEnemyBeamEnergyBall::INPUT_LAYOUT =
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
BirdEnemyBeamEnergyBall::BirdEnemyBeamEnergyBall(CommonResources* resources, BaseEntity* parent, BirdEnemyBeam* beam)
	:
	CollisionEntity(resources,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3(0, 100, 0), DirectX::SimpleMath::Quaternion::Identity)
	,m_model{}
	,m_initialScale{}
	,m_iniialPosition{}
	,m_initialRotate{}
	,m_vertexShader{}
	,m_pixelShader{}
	,m_inputLayout{}
	,m_CBuffer{}
	,m_target{}
	,m_maxScale{}
	,m_beam{beam}
	,m_maxSizeTime{}
	,m_time{}
{
	BaseEntity::SetParent(parent);

	BaseEntity::SetIsGravity(false);
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBeamEnergyBall::~BirdEnemyBeamEnergyBall()
{
	// do nothing.
}


/// <summary>
/// 初期化
/// </summary>
void BirdEnemyBeamEnergyBall::Initialize()
{
	using namespace DirectX::SimpleMath;

	CollisionEntity::Initialize();


	// モデルを読み込む
	m_model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BeamEnergyBall");

	//初期化
	m_maxScale = Params::BIRDENEMY_BEAM_BALL_MAX_SIZE;
	m_maxSizeTime = Params::BIRDENEMY_BEAM_BALL_ACCUMULATIONTIME;
	m_time = 0;

	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), BOX_COLLIDER_SIZE);


}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemyBeamEnergyBall::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	//オブジェクトか描画が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}

	using namespace DirectX::SimpleMath;
	//コンテキストの取得
	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	//コモンステートの作成
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();


	CollisionEntity::Render(view, projection);


	//モデルを描画する
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection, false, [&]()
		{
		});

	//Matriから座標などを取得する
	Vector3 scale;
	Quaternion roatation;
	Matrix matrix = BaseEntity::GetWorldMatrix();
	matrix.Decompose(scale, roatation, m_wordlPosition);

	//当たり判定の描画
	CollisionEntity::GetBounding()->DrawBoundingSphere(m_wordlPosition, view, projection);
	CollisionEntity::GetBounding()->DrawBoundingBox(m_wordlPosition, view, projection);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyBeamEnergyBall::Update(const float& elapsedTime)
{

	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}


	CollisionEntity::Update(elapsedTime);

}


/// <summary>
/// 当たり判定に追加
/// </summary>
/// <param name="collsionManager"></param>
void BirdEnemyBeamEnergyBall::AddCollision(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}

/// <summary>
/// 当たった時に呼び出す関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void BirdEnemyBeamEnergyBall::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);

	using namespace DirectX::SimpleMath;

	switch (tag)
	{
		//プレイヤかステージに当たったら
		case CollisionEntity::CollisionTag::PLAYER:
		case CollisionEntity::CollisionTag::STAGE:
		{
			m_beam->GetStateMahine()->ChangeState(m_beam->GetStateMahine()->GetBirdEnemyBeamIdle());

			//座標を決める
			Vector3 position = m_wordlPosition;
			Vector3 scale = Vector3::One;
			UnknownDataTwo aa = { &position , &scale };
			Messenger::GetInstance()->Notify(GamePlayMessageType::CREATE_EXPLOSION, &aa);

		}
		break;
		default:
			break;
	}
}




