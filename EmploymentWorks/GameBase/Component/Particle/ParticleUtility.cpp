//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2025/1/31
// <file>			ParticleUtility.cpp
// <概要>			パーティクルの基本クラス
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "pch.h"
#include "Particleutility.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="life">生存時間</param>
/// <param name="pos">座標</param>
/// <param name="velocity">速度</param>
/// <param name="accele">加速度</param>
/// <param name="startScale">初期サイズ</param>
/// <param name="endScale">最終サイズ</param>
/// <param name="startColor">初期色</param>
/// <param name="endColor">最終色</param>
ParticleUtility::ParticleUtility(
	float life,
	DirectX::SimpleMath::Vector3 pos,
	DirectX::SimpleMath::Vector3 velocity,
	DirectX::SimpleMath::Vector3 accele,
	DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
	DirectX::SimpleMath::Quaternion startRotate, DirectX::SimpleMath::Quaternion endRotate,
	DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor)
{
	//	与えられた生存時間（s）を取得
	m_startLife =
		m_life = life;

	//	初期位置を取得
	m_position = pos;
	//	移動ベクトルを取得
	m_velocity = velocity;
	//	加速度ベクトルを取得
	m_accele = accele;

	//	初めのサイズを取得
	m_startScale =
		m_nowScale = startScale;
	//	終了のサイズを取得
	m_endScale = endScale;

	m_startRotate 
		= m_nowRotate = startRotate;
	m_endRotate = endRotate;


	//	初めの色を取得
	m_startColor =
		m_nowColor = startColor;
	//	終了の色を取得
	m_endColor = endColor;

	m_addForce = DirectX::SimpleMath::Vector3::Zero;

	m_easingType = NakashiLib::Easing::EasingType::InSine;

	for (int i = 0; i < 3; i++)
	{
		m_easingSize[i] = NakashiLib::Easing::Easing();
	}
	for (int i = 0; i < 4; i++)
	{
		m_easingColor[i] = NakashiLib::Easing::Easing();
	}
}

/// <summary>
/// デストラクタ
/// </summary>
ParticleUtility::~ParticleUtility()
{
}
/// <summary>
/// 更新関数
/// </summary>
/// <returns>生存時間(life)がある間はtrue</returns>
bool ParticleUtility::Update(float elapsedTime)
{
	// 時間経過で進行度
	float t = 1.0f - m_life / m_startLife;
	float speed = elapsedTime / m_startLife;

	m_nowScale.x = m_easingSize[0].Selection(m_easingType, speed, m_startScale.x, m_endScale.x);
	m_nowScale.y = m_easingSize[1].Selection(m_easingType, speed, m_startScale.y, m_endScale.y);
	m_nowScale.z = m_easingSize[2].Selection(m_easingType, speed, m_startScale.z, m_endScale.z);

	// 回転はそのままLerp（必要ならEasing可）
	m_nowRotate = DirectX::SimpleMath::Quaternion::Lerp(m_startRotate, m_endRotate, t);

	// Easingで色変化
	m_nowColor.x = m_easingColor[0].Selection(m_easingType, speed, m_startColor.x, m_endColor.x);
	m_nowColor.y = m_easingColor[1].Selection(m_easingType, speed, m_startColor.y, m_endColor.y);
	m_nowColor.z = m_easingColor[2].Selection(m_easingType, speed, m_startColor.z, m_endColor.z);
	m_nowColor.w = m_easingColor[3].Selection(m_easingType, speed, m_startColor.w, m_endColor.w);

	m_velocity += m_accele * elapsedTime;
	m_velocity += m_addForce * elapsedTime;
	m_position += m_velocity * elapsedTime;
	//	ライフを減らしていく
	m_life -= elapsedTime;
	//	ライフが0未満なら自身を消してもらう
	if (m_life < 0.0f)
	{
		return false;
	}

	return true;
}

void ParticleUtility::SetEasing(NakashiLib::Easing::EasingType easingType)
{
	m_easingType = easingType;


}

