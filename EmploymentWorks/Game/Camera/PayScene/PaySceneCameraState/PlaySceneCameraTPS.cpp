#include "pch.h"
#include "PlaySceneCameraTPS.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Player/Player2.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="stateMachine">ステートマシーン</param>
/// <param name="camera">カメラ</param>
PlaySceneCameraTPS::PlaySceneCameraTPS(PlaySceneCameraStateMachine* stateMachine, PlaySceneCamera* camera)
	:
	m_camera{camera}
	,m_stateMAchine{stateMachine}
	,m_rotationX{}
	,m_rotationY{}
	,m_forward{DirectX::SimpleMath::Vector3::Forward}
{

}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneCameraTPS::~PlaySceneCameraTPS()
{
}

void PlaySceneCameraTPS::Update(const float& elapsedTime)
{
	using namespace DirectX;;
	using namespace DirectX::SimpleMath;

	//マウス操作
	MouseOperation();
	
	Vector3 target = m_camera->GetPlayer()->GetTransform()->GetWorldPosition() +  Vector3(0, 1, 0);

	//X軸回転の計算
	Quaternion rotateX = Quaternion::CreateFromAxisAngle(Vector3::UnitY, XMConvertToRadians(m_rotationX));
	//回転の計算
	Quaternion rotate = Quaternion::CreateFromYawPitchRoll(m_rotationY, m_rotationX, 0.0f);
	// カメラがターゲットからどれくらい離れているか
	Vector3 eye = Vector3::UnitZ * CAMERA_DISTANCE;
	//視点の回転
	eye = Vector3::Transform(eye, rotate);

	eye += target;

	m_camera->SetEyePosition(eye);
	m_camera->SetTargetPosition(target);

}

void PlaySceneCameraTPS::Enter()
{
	//初期値設定
	SetCursorPos(MOUSE_POSITION.x,MOUSE_POSITION.y);

}

void PlaySceneCameraTPS::Exit()
{
}

/// <summary>
/// マウス操作
/// </summary>
void PlaySceneCameraTPS::MouseOperation()
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//マウス座標変数
	POINT mousePosition;
	//マウス座標の取得
	GetCursorPos(&mousePosition);
	//差分を求める
	Vector2 diff;
	diff.x = MOUSE_POSITION.x - mousePosition.x;
	diff.y = MOUSE_POSITION.y - mousePosition.y;
	//移動量の加算
	m_rotationX += diff.y * MOUSE_SENSITIVITY;
	m_rotationY += diff.x * MOUSE_SENSITIVITY;

	//初期値設定
	SetCursorPos(MOUSE_POSITION.x, MOUSE_POSITION.y);
	//上の制限
	if (m_rotationX >= ROTATE_LIMIT)
	{
		m_rotationX = ROTATE_LIMIT;
	}
	//下の制限
	if (m_rotationX <= -ROTATE_LIMIT)
	{
		m_rotationX = -ROTATE_LIMIT;
	}

	//プレイカメラにセット
	m_camera->SetRotationX(m_rotationX);
	m_camera->SetRotationY(m_rotationY);
}
