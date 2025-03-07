#include "DamageVignette.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);



float4 main(PS_INPUT input) : SV_TARGET
{
   
    float2 uv = input.Tex;
    uv -= 0.5f; // UV���W�𒆐S�Ɉړ��i[-0.5, 0.5] �ɕϊ��j

    // ��������̋������v�Z
    float dist = length(uv);

// �O�g�̕��i�ԐF���瓧���ւ̑J�ڔ͈͂̊J�n�ƏI���j
    float vignetteStart = 1.5f; // �ԐF���n�܂�ʒu�i�O�g�j
    float vignetteEnd = 1.33f; // �ԐF�����S�ɓ����ɂȂ�ʒu

    // �A���t�@�l�̌v�Z�i�����x�𐧌�j
    float alpha = smoothstep(vignetteEnd, vignetteStart, dist);

    // �ԐF�̐����i�A���t�@�𔽉f�j
    float4 baseColor = float4(1, 0, 0, alpha);

    // �����͓���
    float innerAlpha = smoothstep(0.0f, vignetteEnd, dist);
    float4 innerColor = float4(1, 0, 0, innerAlpha * time.x);

    // ���ʂ������i�O�g��ԁA�����𓧖��j
    return lerp(innerColor, baseColor,  alpha );

}