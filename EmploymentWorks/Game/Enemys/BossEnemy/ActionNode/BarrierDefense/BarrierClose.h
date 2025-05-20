#pragma once
#include <pch.h>
#include "Game/Interface/IActione.h"

//前方宣言
class CommonResources;
class BarrierDefenseAction;
class Barrier;
class CharacterEntity;

// BarrierCloseクラスを定義する
class BarrierClose : public IAction
{
public:

	static constexpr float CLOSE_TIME = 1.0f;

public:
	// コンストラクタ
	BarrierClose(CommonResources* resources,BarrierDefenseAction* barrierDefenseAction, Barrier* barrier, CharacterEntity* owner);
	// デストラクタ
	~BarrierClose();
	//初期化
	void Initialize() override;
	// 更新処理
	ActionState Update(const float& elapsedTime);
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;


private:

	// 共通リソース
	CommonResources* m_commonResources;
	//バリア防御のコントローラー
	BarrierDefenseAction* m_barrierDefenseAction;
	//バリア
	Barrier* m_barrier;
	//時間
	float m_time;
	//
	CharacterEntity* m_owner;

};

