#include "HitEffects.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);



//�摜��UV�@UV�ɑ΂��Ă̍��W�@
float CalcAlpha(float2 uv, float2 center, float size)
{
    

    return step(distance(uv, float2(center.x, center.y)), size);
}


float4 CalcColor(float2 uv,float size)
{
    float outsideValue = size;
    float insideValue = size - 0.05f;
    //�摜�̒��S
    float2 center = float2(0.5f, 0.5f);
    //���S����̋���
    float Value = distance(uv, center);
    //inside����outside�̊����@�͈͊O�͂O
    float ratio = saturate((Value - insideValue) / (outsideValue - insideValue));
        
    float4 ore = float4(1.0f,0.5f,0.0,1.0f);
    float4 whi = float4(1.0f,1.0f,1.0,1.0f);
    
    float4 color = lerp(ore, whi,ratio);
    
    return color;
    
}

float CalcAlpha2(float2 uv, float2 center, float size)
{
    float alpha = 0;
    //float aspect = 1280.0f / 720.0f;
    //uv.x *= aspect; // �A�X�y�N�g��̒���

    // center�̈ʒu���A�X�y�N�g��ɍ��킹�Ē���
    float2 adjustedCenter = center;

    float Value = distance(uv, center);

    // 0.0f����1.0f�͈̔͂Ɏ��߂A����������
    float x = Value / size;

    alpha = smoothstep(1.0f, 0.75f, x);

    return alpha;
}


//�l���ȏ�Ȃ�O���ȉ��Ȃ�l�����̂܂ܕԂ� 
float ModifySize(float size ,float deffultValue)
{
    //�ȉ��Ȃ�O�@�@�ȏ�Ȃ�P
    float mask = step(size, deffultValue);
    
    return size * mask;
    
}


float4 main(PS_INPUT input) : SV_TARGET
{

    //    �^�����ȃs�N�Z��
    //float4 outputb = float4(1, 0.5f, 0.0f, 1);
    float4 outputb = float4(1.0f, 1.0f, 1.0f, 1);

    //�T�C�Y�̌v�Z
    float size =time.x;
    
    //0.5�ȏ�Ȃ�O�ɂ���
    size = ModifySize(size, 0.5f);
    
    
    
    //�F�����߂�
    outputb = CalcColor(input.Tex,size);
    

   
    //�O�g�̂͂�����Ƃ����~
    outputb.a = CalcAlpha(input.Tex, float2(0.5f, 0.5f), size);
    //�����̂��񂾂񓧖��ɂȂ�~
    outputb.a -= CalcAlpha2(input.Tex, float2(0.5f, 0.5f), size);


    return outputb;
}