//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2025/1/31
// <file>			ParticleUtility.h
// <概要>			パーティクルの基本クラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include "GameBase/Common/Commons.h"
#include "Libraries/Easing.h"
class ParticleUtility
{
public:
	//	関数
	//	コンストラクタ（初期設定）
	ParticleUtility(
		float life,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 velocity,
		DirectX::SimpleMath::Vector3 accele,
		DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
		DirectX::SimpleMath::Quaternion startRotate , DirectX::SimpleMath::Quaternion endRotate,
		DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor);
	//	デストラクタ
	~ParticleUtility();

	//	更新
	bool Update(float elapsedtime);

	//	getter
	const DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }


	const DirectX::SimpleMath::Vector3 GetVelocity() { return m_velocity; }

	const DirectX::SimpleMath::Vector3 GetAccele() { return m_accele; }

	const DirectX::SimpleMath::Vector3 GetNowScale() { return m_nowScale; }
	const DirectX::SimpleMath::Vector3 GetStartScale() { return m_startScale; }
	const DirectX::SimpleMath::Vector3 GetEndScale() { return m_endScale; }

	const DirectX::SimpleMath::Quaternion GetNowRotate() { return m_nowRotate; }
	const DirectX::SimpleMath::Quaternion GetStartRotate() { return m_startRotate; }
	const DirectX::SimpleMath::Quaternion GetEndRotate() { return m_endRotate; }

	const float GetLife() { return m_life; }
	const float GetStartLife() { return m_startLife; }
	const DirectX::SimpleMath::Color GetNowColor() { return m_nowColor; }
	const DirectX::SimpleMath::Color GetStartColor() { return m_startColor; }
	const DirectX::SimpleMath::Color GetEndColor() { return m_endColor; }

	const DirectX::SimpleMath::Vector3 GetAddForce() { return m_addForce; }
	void SetAddForce(DirectX::SimpleMath::Vector3 addforce) { m_addForce = addforce; }

	// イージングをセット
	void SetEasing(NakashiLib::Easing::EasingType easingType);
private:
	//	関数
	//	座標
	DirectX::SimpleMath::Vector3 m_position;

	// 回転
	DirectX::SimpleMath::Quaternion m_startRotate;
	DirectX::SimpleMath::Quaternion m_nowRotate;
	DirectX::SimpleMath::Quaternion m_endRotate;

	//	速度
	DirectX::SimpleMath::Vector3 m_velocity;
	//	加速度
	DirectX::SimpleMath::Vector3 m_accele;

	//	スケール
	DirectX::SimpleMath::Vector3 m_nowScale;
	DirectX::SimpleMath::Vector3 m_startScale;
	DirectX::SimpleMath::Vector3 m_endScale;

	//	生存時間
	float m_life;
	float m_startLife;

	//	カラー
	DirectX::SimpleMath::Color m_nowColor;
	DirectX::SimpleMath::Color m_startColor;
	DirectX::SimpleMath::Color m_endColor;

	// 追加速度
	DirectX::SimpleMath::Vector3 m_addForce;

	// イージングのタイプ
	NakashiLib::Easing::EasingType m_easingType;
	// 大きさ用イージング
	NakashiLib::Easing m_easingSize[3];
	// 色用イージング
	NakashiLib::Easing m_easingColor[4];

};
