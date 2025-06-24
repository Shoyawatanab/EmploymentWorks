cbuffer ConstBuffer	: register(b0)
{
    float4 windowSize;
	float4 position;
    float4 size;
    float4 color;
    float4 clipRange;
    float4 viewRange;    //�\���͈�
	float4 FillAmount;  //x:���@y:�c
	

};

struct VS_INPUT
{
	float3 pos : POSITION;
	float2 tex : TEXCOORD;
};

struct PS_INPUT
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};