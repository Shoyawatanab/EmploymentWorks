#pragma once
#include <unordered_map>

class Animation2;

class AnimationController
{
public:
	//アニメーションの実行状態
	enum class ExecutionState
	{
		NONE        //通常
		,TRIIGER	//１回だけ実行
		,FLOAT		//
	};

	//状態遷移のフロー
	enum class TransitionState
	{
		UNIDIRECTIONAL       //片方向
		, BIDIRECTIONAL      //双方向
	};

public:
	//コンストラクタ
	AnimationController();
	//デストラクタ
	virtual ~AnimationController();
	//更新処理
	void Update(const float& deltaTime);

	//アニメーションの追加
	void AddAnimatoin(std::unique_ptr<Animation2> animatino);
	//アニメーションの切り替え
	void SetTrigger(std::string animationName);
	//アニメーションの切り替え　対よりも大きい場合のみ変更
	void SetFloat(std::string animationName,float value);
	//状態遷移フローの作成
	void CreateTransitionFlow(std::string state1, std::string state2,TransitionState transitionState);
private:

	//状態遷移リストに追加
	void AddTransitionList(std::string state1, std::string state2);

private:

	//デフォルトアニメーション

	//実行アニメーション
	Animation2* m_currentAnimation;
	//アニメーションの格納変数
	std::vector<std::unique_ptr<Animation2>> m_animations;

	//状態遷移の保存
	std::unordered_map<std::string,std::vector<std::string>> m_stateTransitionList;



};