#pragma once
#include <pch.h>
#include "Interface/IBeamState.h"
class CommonResources;

class Boomerang;
class Beam;

// BeamAttackクラスを定義する
class BeamAttack : public IBeamState
{
public:





public:
	// コンストラクタ
	BeamAttack();
	// デストラクタ
	~BeamAttack();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(CommonResources* resoure, Beam* beam);


private:

private:

	// 共通リソース
	CommonResources* m_commonResources;

	Beam* m_beam;


};

