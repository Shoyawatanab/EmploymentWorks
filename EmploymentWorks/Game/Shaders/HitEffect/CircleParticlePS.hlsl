#include "CircleParticle.hlsli"

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

//���񂾂񓧖��ɕω������� 
//color�摜���Atime : �o�ߎ��ԁAfadeStartTime : �t�F�[�h�̊J�n���ԁAfadeDuration : �t�F�[�h�̏I���܂ł̎���
float4 fadeOut(float4 color, float time, float fadeStartTime, float fadeDuration)
{
    // �t�F�[�h�i�s�x���v�Z�i0�`1�j
    float fadeProgress = saturate((time - fadeStartTime) / fadeDuration);

    // �t�F�[�h�A�E�g��K�p�i�t�F�[�h�i�s�x���i�ނقǓ����Ɂj
    float fadeFactor = 1.0f - fadeProgress;

    // �A���t�@�l�𒲐�
    color.a *= fadeFactor;

    return color;
}

float4 main(PS_INPUT input) : SV_TARGET
{

    //    �^�����ȃs�N�Z��
    float4 outputb = float4(1.0f, 1.0f, 1.0f, 1);
    //�摜�̒��S
    float2 center = float2(0.5f, 0.5f);
    
    
    //��������
    float lifeTime = 0.5f;
    
    //�T�C�Y�̌v�Z
    float size = time.x;
    
    //�ő�T�C�Y�𒴂��Ȃ��悤��
    size = min(size, 0.5f);
    //�F�����߂�
    outputb = CalcColor(input.Tex,size);
    //�O�g�̂͂�����Ƃ����~
    outputb.a = CalcAlpha(input.Tex, center, size);
    //�����̂��񂾂񓧖��ɂȂ�~
    outputb.a -= CalcAlpha2(input.Tex, center, size);

    //�ő�T�C�Y�ɂȂ����炾�񂾂񓧖��ɕω�������
    outputb = fadeOut(outputb, time.x, lifeTime, 0.15f);
    
    return outputb;
}