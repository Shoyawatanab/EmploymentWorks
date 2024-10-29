#include "Fade.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	^‚Á•‚È”Âƒ|ƒŠƒSƒ“
    float4 outputb = float4(0, 0, 0, 1);

    outputb.a = sin(time.x);
	
    return outputb;
}