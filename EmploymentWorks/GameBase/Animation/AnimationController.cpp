#include "pch.h"
#include "AnimationController.h"
#include "GameBase/Animation/Animation2.h"

/// <summary>
/// コンストラクタ
/// </summary>
AnimationController::AnimationController()
	:
	m_animations{}
	,m_currentAnimation{}
	,m_stateTransitionList{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
AnimationController::~AnimationController()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void AnimationController::Update(const float& deltaTime)
{
	m_currentAnimation->Update(deltaTime);
}



/// <summary>
/// アニメーションの追加
/// </summary>
/// <param name="animatino"></param>
void AnimationController::AddAnimatoin(std::unique_ptr<Animation2> animatino)
{
	//既に存在するか探す
	auto it = std::find(m_animations.begin(), m_animations.end(), animatino);

	//すでにあれば
	if (it != m_animations.end())
	{
		return;
	}
	//追加
	m_animations.push_back(std::move(animatino));

}

/// <summary>
/// アニメーションの切り替え　1回だけ実行
/// </summary>
/// <param name="animationName">アニメーション名</param>
void AnimationController::SetTrigger(std::string animationName)
{
}

/// <summary>
/// アニメーションの切り替え
/// </summary>
/// <param name="animationName"></param>
/// <param name="value"></param>
void AnimationController::SetFloat(std::string animationName, float value)
{
}


/// <summary>
/// 状態遷移の作成　片方向の時は１から２のフローを作成　
/// </summary>
/// <param name="state1">状態１</param>
/// <param name="state2">情愛２</param>
/// <param name="transitionState">片方向か双方向化</param>
void AnimationController::CreateTransitionFlow(std::string state1, std::string state2, TransitionState transitionState)
{

	switch (transitionState)
	{
		case AnimationController::TransitionState::UNIDIRECTIONAL:
			//片方向
			AddTransitionList(state1, state2);
			break;
		case AnimationController::TransitionState::BIDIRECTIONAL:
			//両方向追加
			AddTransitionList(state1, state2);
			AddTransitionList(state2, state1);
			break;
		default:
			break;
	}

}

/// <summary>
/// 状態遷移リストに追加
/// </summary>
/// <param name="state1">状態１</param>
/// <param name="state2">状態２</param>
void AnimationController::AddTransitionList(std::string state1, std::string state2)
{
	
	; auto& it = m_stateTransitionList[state1];

	// すでに string2 が登録されているかチェック
	if (std::find(it.begin(), it.end(), state2) == it.end())
	{
		// 登録されていなければ追加
		it.push_back(state2); 
	}

}
