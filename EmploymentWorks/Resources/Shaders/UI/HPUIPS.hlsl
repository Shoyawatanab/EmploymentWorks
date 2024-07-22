#include "UI.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 output = tex.Sample(samLinear, input.tex);


    // テクスチャ座標xがsmoothValueを超えたら透明にする
    float smoothValue = input.color.x;
    if (input.tex.x > smoothValue)
    {
        output.a = 0.0f; // 完全に透明
    }
    else
    {
        output.a = 1.0f; // 完全に不透明
    }
    return output;
}