#include "pch.h"
#include "BarrierStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="barrier">バリア</param>
BarrierStateMachine::BarrierStateMachine(CommonResources* resources
	, Barrier* barrier)
	:
	m_currentState{}
{
	m_generate = std::make_unique<BarrierGenerate>(resources,barrier);
	m_shrink = std::make_unique<BarrierShrink>(resources, barrier);
}

/// <summary>
/// デストラクタ
/// </summary>
BarrierStateMachine::~BarrierStateMachine()
{
}



/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="startState">初期ステート</param>
void BarrierStateMachine::Initialize(CommonResources* resources, IState* startState)
{
	UNREFERENCED_PARAMETER(resources);
	


	m_currentState = startState;

	m_currentState = m_generate.get();

}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BarrierStateMachine::Update(const float& elapsedTime)
{
	m_currentState->Update(elapsedTime);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BarrierStateMachine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_currentState->Render(view, projection);
}

/// <summary>
/// ステートの切り替え
/// </summary>
/// <param name="nextState">次のステート</param>
void BarrierStateMachine::ChangeState(IState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();



}


