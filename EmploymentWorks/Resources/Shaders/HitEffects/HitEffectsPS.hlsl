#include "HitEffects.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);



//画像のUV　UVに対しての座標　
float CalcAlpha(float2 uv, float2 center, float size)
{
    

    return step(distance(uv, float2(center.x, center.y)), size);
}


float4 CalcColor(float2 uv,float size)
{
    float outsideValue = size;
    float insideValue = size - 0.05f;
    //画像の中心
    float2 center = float2(0.5f, 0.5f);
    //中心からの距離
    float Value = distance(uv, center);
    //insideからoutsideの割合　範囲外は０
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
    //uv.x *= aspect; // アスペクト比の調整

    // centerの位置をアスペクト比に合わせて調整
    float2 adjustedCenter = center;

    float Value = distance(uv, center);

    // 0.0fから1.0fの範囲に収めつつ、調整をする
    float x = Value / size;

    alpha = smoothstep(1.0f, 0.75f, x);

    return alpha;
}


//値が以上なら０を以下なら値をそのまま返す 
float ModifySize(float size ,float deffultValue)
{
    //以下なら０　　以上なら１
    float mask = step(size, deffultValue);
    
    return size * mask;
    
}


float4 main(PS_INPUT input) : SV_TARGET
{

    //    真っ黒なピクセル
    //float4 outputb = float4(1, 0.5f, 0.0f, 1);
    float4 outputb = float4(1.0f, 1.0f, 1.0f, 1);

    //サイズの計算
    float size =time.x;
    
    //0.5以上なら０にする
    size = ModifySize(size, 0.5f);
    
    
    
    //色を決める
    outputb = CalcColor(input.Tex,size);
    

   
    //外枠のはっきりとした円
    outputb.a = CalcAlpha(input.Tex, float2(0.5f, 0.5f), size);
    //内側のだんだん透明になる円
    outputb.a -= CalcAlpha2(input.Tex, float2(0.5f, 0.5f), size);


    return outputb;
}