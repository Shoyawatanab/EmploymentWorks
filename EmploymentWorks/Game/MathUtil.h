#pragma once

namespace MathUtil
{

    template<typename T>
    inline T Lerp(const T& a, const T& b, float t)
    {
        return a + (b - a) * t;
    }



    /// <summary>
    /// Vector3‚ðQuaternion‚É•ÏŠ·
    /// </summary>
    /// <param name="vector3"></param>
    /// <returns></returns>
    inline DirectX::SimpleMath::Quaternion ChangeVector3ToQuaternion(
        DirectX::SimpleMath::Vector3 vector3
    )
    {
       return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
            DirectX::XMConvertToRadians(vector3.y),
            DirectX::XMConvertToRadians(vector3.x),
            DirectX::XMConvertToRadians(vector3.z));

    }


}
