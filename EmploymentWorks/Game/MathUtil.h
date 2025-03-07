#pragma once

namespace MathUtil
{

    template<typename T>
    inline T Lerp(const T& a, const T& b, float t)
    {
        return a + (b - a) * t;
    }

}
