//	共通で必要となる構造体を、ヘッダファイルとして抜き出し
cbuffer ConstBuffer	: register(b0)
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
	float4 diffuse;
    float4 time;

};

struct VS_INPUT
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;

};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;

};