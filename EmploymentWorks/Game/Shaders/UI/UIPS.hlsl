#include "UI.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	指定された画像の表示
    float4 output = tex.Sample(samLinear, input.tex);

    float4 smoothValue = input.color;
    output.a *= lerp(1.0f, 0.0f, smoothstep(smoothValue, smoothValue + 0.01f, input.tex.x)); //tex.yで上下に移動可能

    //全体の透明度をかける
    output *= diffuse;

    return output;
    
}