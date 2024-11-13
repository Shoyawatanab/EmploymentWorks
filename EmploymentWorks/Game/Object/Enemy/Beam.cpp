/*
	@file	Beam.cpp
	@brief	ビームクラス
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

#include "Libraries/MyLib/Bounding.h"
#include "Game/DetectionCollision/CollisionManager.h"

#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/BossEnemy.h"
#include "Game/Object/Enemy/BeamModel.h"

static const int MAXMODELS = 50;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Beam::Beam()
	:
	m_commonResources{},
	m_position{},
	m_rotate{},
	m_generationInterval{},
	m_preliminaryActionTime{}
	,m_enemy{}
	,m_player{}
	,m_models{}
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
void Beam::Initialize(CommonResources* resources, Player* player, Enemy* enemy)
{
	using namespace DirectX::SimpleMath;


	assert(resources);
	m_commonResources = resources;
	m_player = player;
	m_enemy = enemy;



	m_position = DirectX::SimpleMath::Vector3(0, 10, 0);

	m_initialRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(90.0f));
	m_rotate = DirectX::SimpleMath::Quaternion::Identity;


	m_models = std::make_unique<BeamModel>();
	m_models->Initialize(m_commonResources, DirectX::SimpleMath::Vector3::Zero, 2.5f);

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Beam::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);




}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Beam::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	//auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//auto states = m_commonResources->GetCommonStates();

	for (auto& bounding : m_bounding)
	{
		bounding->DrawBoundingSphere(view, projection);
	}


	for (auto& Draw : m_drawModels)
	{
		Draw->Render(view, projection);
	}

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Beam::Finalize()
{
	// do nothing.

}


/// <summary>
/// ビームの攻撃
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns>true:攻撃中　false:攻撃終了</returns>
bool Beam::Attack(float elapsdTime)
{
	////予備動作
	//if (m_preliminaryActionTime < 2)
	//{
	//	//if (m_preliminaryActionTime == 0)
	//	//{
	//	//	m_enemy->RegistrationRungingAnimation("Beam");
	//	//}

	//	m_preliminaryActionTime += elapsdTime;
	//	return true;
	//}

	//予備動作が終わってから１回だけ呼びたい
	if (m_bounding.empty())
	{
		//
		m_startPos = m_enemy->GetBeamStartPosition();
		//プレイヤの座標をビームの終わりに
		m_endPos = m_player->GetPosition();

		//ビームの軌道を求める
		DirectX::SimpleMath::Vector3 Orbit = m_endPos - m_startPos;

		//軌道の距離を求める
		float Lenght = Orbit.Length();

		//生成距離
		float a = 1;

		//分割数を決める
		float Split = Lenght / a;

		Orbit.Normalize();
		//分割数をもとに座標を決める
		for (int i = 0; i < Split; i++)
		{
			//生成座標を決める

			BoundingParameter bounding;
			bounding.Position  = m_startPos + Orbit * a * static_cast<float>( i);
			bounding.Life = 5;
			
			m_keepBoundingParameter.push_back(bounding);
		}

		//最後のところをいきすぎないようにするかも


		//１個目の生成
		//座標の先頭を使用
		CreateBounding(m_keepBoundingParameter.front().Position, 3.0f);
		//先頭の値を渡す
		m_boundingParameter.push_back(m_keepBoundingParameter.front());
		//座標の更新
		m_models->SetPos(m_keepBoundingParameter.front().Position);

		//描画モデルのコピー
		auto Copy = std::make_unique<BeamModel>(*m_models);

		m_drawModels.push_back(std::move(Copy));

		//先頭の座標を削除する
		m_keepBoundingParameter.erase(m_keepBoundingParameter.begin());


	}


	//攻撃
	//2個目以降の生成
	if (m_generationInterval >= 0.3f && !m_keepBoundingParameter.empty())
	{
		//座標の先頭を使用
		CreateBounding(m_keepBoundingParameter.front().Position, 3.0f);
		//先頭の値を渡す
		m_boundingParameter.push_back(m_keepBoundingParameter.front());
		//座標の更新
		m_models->SetPos(m_keepBoundingParameter.front().Position);

		//描画モデルのコピー
		auto Copy = std::make_unique<BeamModel>(*m_models);

		m_drawModels.push_back(std::move(Copy));


		//先頭の座標を削除する
		m_keepBoundingParameter.erase(m_keepBoundingParameter.begin());

		m_generationInterval = 0;
	}

	//生成時間を減らす
	for (auto& bouding : m_boundingParameter)
	{
		bouding.Life -= elapsdTime;


		if (bouding.Life <= 0)
		{
			//先頭のBoundingの削除
			m_bounding.erase(m_bounding.begin());
			//先頭のBoundingParameterの削除
			m_boundingParameter.erase(m_boundingParameter.begin());
			//先頭の削除
			m_drawModels.erase(m_drawModels.begin());
		}

	}

	if (m_bounding.empty())
	{
		//予備動作の時間の初期化
		m_preliminaryActionTime = 0;
		//m_enemy->RegistrationRungingAnimation("BeamEnd");
		m_enemy->SetRunnginAnimationName("BeamEnd");
		//攻撃終了
		return false;
	}



	m_generationInterval += elapsdTime;
	return true;
}


/// <summary>
/// Boundingクラスの作成
/// </summary>
/// <param name="Pos"></param>
/// <param name="radius"></param>
void Beam::CreateBounding(DirectX::SimpleMath::Vector3 Pos, float radius)
{

	auto bounding = std::make_unique<Bounding>();
	bounding->CreateBoundingSphere(m_commonResources,Pos, radius);


	m_bounding.push_back(std::move(bounding));


}


