#include "WorldSpaceUI.hlsli"

static const float2 center = float2(-1, 1);

static const unsigned int vnum = 4;

//wが0だと行列計算がおかしくなるので1に変更
static const float4 offset_array[vnum] =
{
	float4( -0.5f,  0.5f, 0.0f, 1.0f),	// 左上
	float4( 0.5f,  0.5f, 0.0f, 1.0f),	// 右上
	float4( -0.5f,  -0.5f, 0.0f, 1.0f),	// 左下
	float4( 0.5f,  -0.5f, 0.0f, 1.0f),	// 右下

};


static const float2 offset_UV[vnum] =
{
    float2(0.0f, 0.0f), //	左上
	float2(1.0f, 0.0f), //	右上
	float2(0.0f, 1.0f), //	左下
	float2(1.0f, 1.0f), //	右下

};

[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream< PS_INPUT > output
)
{
    
    float cosA = cos(rotate.x);
    float sinA = sin(rotate.x);

    for (uint i = 0; i < vnum; i++)
    {
        PS_INPUT element;
        

        
        //大きさの反映
        float4 local = offset_array[i] * size / 300;

    // 回転
        float4 rotated = local;
        rotated.x = local.x * cosA - local.y * sinA;
        rotated.y = local.x * sinA + local.y * cosA;
        
    // ビュー拡大縮小
        rotated.xy *= viewRange.xy;


        //中心点から座標を計算
        element.pos = input[0].pos + mul(rotated, matWorld);
        element.pos = mul(element.pos, matView);
        element.pos = mul(element.pos, matProj);
        
        
    // UVの計算
        element.tex = float2(
        clipRange.x + clipRange.z * offset_UV[i].x,
        clipRange.y + clipRange.w * offset_UV[i].y
        );


        
        output.Append(element);
    }

    output.RestartStrip();
	
}