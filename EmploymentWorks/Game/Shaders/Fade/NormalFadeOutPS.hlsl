#include "Fade.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	�^�����Ȕ|���S��
    float4 outputb = float4(0, 0, 0, 1);

    //�o�ߎ���
    float time = Time.x;
    
    //�ő厞��
    float maxTime = Time.y;
    //�i�s����
    float ratio = time / maxTime;
    
    outputb.a = lerp(1.0f,0.0f,ratio);
	
    return outputb;
}