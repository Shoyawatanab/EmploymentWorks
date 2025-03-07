#include "pch.h"
#include "BoomerangStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BoomerangStateMachine::BoomerangStateMachine()
	:
	m_currentState{}
	,m_idle{}
	,m_getReady{}
{
	m_idle = std::make_unique<BoomerangIdle>();
	m_getReady = std::make_unique<BoomerangGetReady>();
	m_throw = std::make_unique<BoomerangThrow>();
	m_repelled = std::make_unique<BoomerangRepelled>();
	m_drop = std::make_unique<BoomerangDrop>();
}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangStateMachine::~BoomerangStateMachine()
{
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="boomerang">ブーメラン</param>
/// <param name="player">プレイヤ</param>
/// <param name="targetMarker">ターゲットマーカー</param>
/// <param name="tpsCamera">TPSカメラ</param>
void BoomerangStateMachine::AddPointer(Boomerang* boomerang, Player* player, TargetMarker* targetMarker, WataLib::TPS_Camera* tpsCamera)
{
	m_idle->AddPointer(player, boomerang);
	m_getReady->AddPointer(boomerang);
	m_throw->AddPointer(boomerang,player,targetMarker,tpsCamera);
	m_repelled->AddPointer(boomerang);
	m_drop->AddPointer(boomerang);
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="startState">初期ステート</param>
void BoomerangStateMachine::Initialize(CommonResources* resources, IState* startState)
{
	//初期化
	m_idle->Initialize(resources);
	m_getReady->Initialize(resources);
	m_throw->Initialize(resources);
	m_repelled->Initialize(resources);
	m_drop->Initialize(resources);

	//ステートを設定
	m_currentState = startState;
	m_currentState->Enter();


}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangStateMachine::Update(const float& elapsedTime)
{
	//ステートの更新
	m_currentState->Update(elapsedTime);
}

void BoomerangStateMachine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	
	m_currentState->Render(view, projection);
}


/// <summary>
/// ステートの切り替え
/// </summary>
/// <param name="nextState">次のステート</param>
void BoomerangStateMachine::ChangeState(IState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();



}


