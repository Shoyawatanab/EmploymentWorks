#include "LockOnUI.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 output = tex.Sample(samLinear, input.tex);

// �����x���}�s�ɕω�������
    float smoothValue = input.color;
    float alpha = lerp(1.0f, 0.0f, smoothstep(smoothValue, smoothValue + 0.1f, input.tex.x));
    output.a *= alpha;

    //// �e�N�X�`�����Wx��smoothValue�𒴂����瓧���ɂ���
    //float smoothValue = input.color.x;
    //if (input.tex.x > smoothValue)
    //{
    //    output.a = 0.0f; // ���S�ɓ���
    //}
    //else
    //{
    //    output.a = 1.0f; // ���S�ɕs����
    //}
    return output;
}