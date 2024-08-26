/*
	@file	Judgement.cpp
	@brief	いろいろな判定をするクラス
*/
#include "pch.h"
#include "Game/Screen.h"
#include "Libraries/MyLib/Judgement.h"

#include <cassert>
#include <random>

#include "Libraries/MyLib/Bounding.h"


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
mylib::Judgement::Judgement()
    :
    m_boundings{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
mylib::Judgement::~Judgement()
{
	// do nothing.
}

int mylib::Judgement::GetRandom(int min, int max)
{
    //ランダムなシード値を使って乱数生成器を初期化
    static std::random_device seed;
    static std::mt19937 engine(seed());

    //	乱数を範囲内で生成
    return engine() % (max - min) + min;
}


 
/// <summary>
/// 扇形ないかどうか
/// </summary>
/// <param name="JudgmentPos">判定してほしい座標</param>
/// <param name="Direction">扇形の方向</param>
/// <param name="Center">扇形の中心座標</param>
/// <param name="radius">扇形の半径</param>
/// <param name="angle">扇形の角度</param>
/// <returns></returns>
bool mylib::Judgement::IsWithinTheSector(DirectX::SimpleMath::Vector3 JudgmentPos, DirectX::SimpleMath::Vector3 Direction, DirectX::SimpleMath::Vector3 Center, float radius, float angle)
{

	
    // 1. JudgmentPosとCenterの間のベクトルを計算
    DirectX::SimpleMath::Vector3 toTarget = JudgmentPos - Center;

    // 2. そのベクトルの長さがradius以下かをチェック
    float distance = toTarget.Length();

    if (distance > radius) {
        return false;  // 半径外なので扇形の外
    }

    // 3. Directionベクトルを正規化する
    Direction.Normalize();

    // 4. toTargetベクトルを正規化する
    toTarget.Normalize();

    // 5. DirectionベクトルとtoTargetベクトルの内積を求める
    float dotProduct = Direction.Dot( toTarget);

    // 6. 内積から角度を求める
    float cosAngle = cosf(DirectX::XMConvertToRadians(angle / 2.0f));

    // 7. 角度が指定された扇形の角度内に収まるかどうかを判定
    return dotProduct >= cosAngle;

}

/// <summary>
/// 登録されたBoundingとRayとの当たり判定
/// </summary>
/// <param name="ray">Ray</param>
/// <param name="distance">Rayの距離</param>
/// <returns>true: 当たっている　,false当たっていない</returns>
bool mylib::Judgement::IsRayToBoundingBox(DirectX::SimpleMath::Ray ray, float distance)
{

    for (auto& object : m_boundings)
    {
        //当たっていたら
        if (object->GetBoundingBox()->Intersects(ray.position, ray.direction, distance))
        {
            return true;
        }
    }


    //当たっていない
    return false;

}

/// <summary>
/// 割合を求める
/// </summary>
/// <param name="value">値</param>
/// <param name="maxValue">最大値</param>
/// <returns></returns>
float mylib::Judgement::GetRatio(float value, float maxValue)
{


    if (maxValue == 0.0f)
    {
        return 0.0f;
    }

    return value / maxValue;
}

/// <summary>
/// 距離を求める
/// </summary>
/// <param name="Pos1">座標１</param>
/// <param name="Pos2">座標２</param>
/// <returns>float型の距離</returns>
float mylib::Judgement::GetLenght(DirectX::SimpleMath::Vector3 Pos1, DirectX::SimpleMath::Vector3 Pos2)
{

    return (Pos1 - Pos2).Length();
}








