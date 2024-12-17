#pragma once
#include <pch.h>
#include "Interface/IBeamState.h"
class CommonResources;

class Boomerang;
class Beam;

//予備動作クラス

// BeamPreliminaryActionクラスを定義する
class BeamPreliminaryAction : public IBeamState
{
public:





public:
	// コンストラクタ
	BeamPreliminaryAction();
	// デストラクタ
	~BeamPreliminaryAction();
	// 初期化する
	void Initialize();

	// 更新する
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(CommonResources* resoure,Beam* beam);


private:

private:

	// 共通リソース
	CommonResources* m_commonResources;

	Beam* m_beam;

	float m_time;

	float m_particleCreateTime;

};

