
#include "pch.h"
#include "Game/Object/Boomerang/BoomerangOrbit.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/BossEnemy.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/Camera/TPS_Camera.h"
#include "Game/Scene/PlayScene.h"

const float SPEED = 5.0f;

const DirectX::SimpleMath::Vector3 AxisOfRotation(0,1,0);  //回転軸


static float Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

// コンストラクタ
BoomerangOrbit::BoomerangOrbit(Boomerang* boomerang, Player* player, Enemy* enemy,PlayScene* playScene)
	:
	m_commonResources{},
	m_boundingSphereLeftLeg{},
	m_boomerang{ boomerang },
	m_player{ player }
	, m_enemy{ enemy },
	m_index{},
	m_moveSpeed{},

	m_transformRatio{},
	m_startIndex{},
	m_totalTime{}
	,m_playScene{playScene}
{
}

// デストラクタ
BoomerangOrbit::~BoomerangOrbit()
{

}

// 初期化する
void BoomerangOrbit::Initialize(CommonResources* resources)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_commonResources = resources;


	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();


	// 左脚境界球を生成する
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// 左脚境界球の半径を設定する
	m_boundingSphereLeftLeg.Radius = 0.01;

	m_csv = std::make_unique<CSV>();
	m_spherePos =  m_csv->LoadCSVBoomerang();

	for (int i = 0; i < m_spherePos.size(); i++)
	{
		m_moveSpherePos.emplace_back(DirectX::SimpleMath::Vector3());
	}

	m_primitveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);


	m_moveSpeed = SPEED;
	m_initialRotate = Quaternion::Identity;
	m_direction = Vector3::Zero;

	m_effect = std::make_unique<BasicEffect>(device);
	m_effect->SetVertexColorEnabled(false);
	
	// 入力レイアウトを作成する
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionColor>(
			device,
			m_effect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);



}



// 更新する
void BoomerangOrbit::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;

	m_index = static_cast<int>( m_spherePos.size() - 1);
	m_startIndex = m_index;
	m_transformRatio = 0;
	m_totalTime = 0;

	m_initialRotate = m_boomerang->GetRotate();
	m_position = m_boomerang->GetPosition();
	//m_target = m_enemy->GetPosition();

	m_linePos.clear();


	//カメラの正面ベクトルの取得
	m_target = m_player->GetTPS_Camera()->GetCameraForward();

	//距離を書ける
	float rate = m_playScene->GetSlowMotionProgressRate() * 1.5f;
	//
	rate = std::min(rate, 1.0f);
	//
	float length = Lerp(5.0f, 17.0f, rate);
	//
	m_target *= length;
	//カメラのターゲットを足す
	m_target += m_player->GetTPS_Camera()->GetTargetPosition();


	Matrix SphereMatrix = Matrix::Identity;
	SphereMatrix = Matrix::CreateFromQuaternion(m_player->GetTPS_Camera()->GetRotationX());
	//プレイヤと敵の距離
	Vector3 PlayerToEnemyDistance = m_target - m_player->GetPosition();
	//高さを０にする
	PlayerToEnemyDistance.y = 0;

	////ロックオン状態じゃなければ
	//if (!m_player->GetIsLockOn())
	//{
	//	//距離を自分で決めたものにする
	//	m_target = Vector3(0, 3, 4);
	//	PlayerToEnemyDistance = m_target;

	//}

	//距離をflaotに変換して半分にする
	float PlayerToEnemyLenght = PlayerToEnemyDistance.Length() / 2;

	//回転の地点を回転させる
	for (int i = 0; i < m_spherePos.size(); i++)
	{
		//基準点
		Vector3 Pos = m_spherePos[i];
		//Sphereとゼロ地点の距離
		Vector3 Distance = Pos - Vector3::Zero;
		//上の距離をfloatがたに変換
		float Lenght = Distance.Length();
		//敵との距離とSphereとの距離の倍率を求める
		float Magnification = PlayerToEnemyLenght / Lenght;
		Distance *= Magnification;
		Pos = Distance;;
		//距離の半分を加算
		Pos.z -= PlayerToEnemyLenght;


		//一時的に保存する
		m_moveSpherePos[i] = Pos;
		//プレイヤの高さに合わせる
		m_moveSpherePos[i].y = m_player->GetPosition().y;


	}


	float a;
	//高さ調整
	for (int i = 0; i < m_spherePos.size(); i++)
	{
		//初期値点から一番遠いところの距離と今の座標の割合を求める
		a = (m_moveSpherePos[i].z - m_moveSpherePos[0].z) / (m_moveSpherePos[3].z - m_moveSpherePos[0].z);
		m_moveSpherePos[i].y = Lerp(m_player->GetPosition().y, m_target.y, a);
	}


	for (int i = 0; i < m_spherePos.size(); i++)
	{

		//プレイヤの回転をもとに回転させる
		m_moveSpherePos[i] = Vector3::Transform(m_moveSpherePos[i], SphereMatrix);
		//原点からになっているからブーメランの位置を加算する
		m_moveSpherePos[i].x += m_position.x;
		m_moveSpherePos[i].z += m_position.z;

	}





	SplineCurve(elapsedTime);



  }


void BoomerangOrbit::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// 各種パラメータを更新する
	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);// ブレンドステート
	context->OMSetDepthStencilState(states->DepthDefault(), 0);		// 深度バッファ/ステンシルバッファ
	context->RSSetState(states->CullCounterClockwise());			// カリング
	context->IASetInputLayout(m_inputLayout.Get());					// 入力レイアウト


	m_effect->SetView(view);
	m_effect->SetProjection(projection);
	m_effect->Apply(context);



	if (m_linePos.size() != 0)
	{

		m_primitveBatch->Begin();
		
		for (int i = 0; i < m_linePos.size() - 1; i++)
		{


			m_primitveBatch->DrawLine(m_linePos[i], m_linePos[i + 1]);
			
		}

		m_primitveBatch->End();

	}


}


void BoomerangOrbit::Finalize()
{

}

/// <summary>
/// スプライン曲線
/// </summary>
/// <param name="elapsedTime"></param>
void BoomerangOrbit::SplineCurve(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	while (m_index <= m_startIndex * 2 + 1)
	{

		float distance = (m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()] -
			m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()]).Length();
		//移動割合
		m_transformRatio = m_totalTime * m_moveSpeed / distance;

		Vector3 Pos = m_boomerang->GetPosition();
		Pos = Vector3::CatmullRom(
			m_moveSpherePos[(m_index + 0) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 3) % m_moveSpherePos.size()],
			m_transformRatio
		);

		DirectX::VertexPositionColor linePos;
		linePos.position = Pos;

		m_linePos.emplace_back(linePos);

		if (m_transformRatio > 1.0f)
		{
			m_index++;
			m_totalTime = 0.0f;
		}




		m_totalTime += elapsedTime;
	}
}