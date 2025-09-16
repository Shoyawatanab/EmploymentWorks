#include "WorldSpaceUI.hlsli"

static const float2 center = float2(-1, 1);

static const unsigned int vnum = 4;

//w��0���ƍs��v�Z�����������Ȃ�̂�1�ɕύX
static const float4 offset_array[vnum] =
{
	float4( -0.5f,  0.5f, 0.0f, 1.0f),	// ����
	float4( 0.5f,  0.5f, 0.0f, 1.0f),	// �E��
	float4( -0.5f,  -0.5f, 0.0f, 1.0f),	// ����
	float4( 0.5f,  -0.5f, 0.0f, 1.0f),	// �E��

};


static const float2 offset_UV[vnum] =
{
    float2(0.0f, 0.0f), //	����
	float2(1.0f, 0.0f), //	�E��
	float2(0.0f, 1.0f), //	����
	float2(1.0f, 1.0f), //	�E��

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
        

        
        //�傫���̔��f
        float4 local = offset_array[i] * size / 300;

    // ��]
        float4 rotated = local;
        rotated.x = local.x * cosA - local.y * sinA;
        rotated.y = local.x * sinA + local.y * cosA;
        
    // �r���[�g��k��
        rotated.xy *= viewRange.xy;


        //���S�_������W���v�Z
        element.pos = input[0].pos + mul(rotated, matWorld);
        element.pos = mul(element.pos, matView);
        element.pos = mul(element.pos, matProj);
        
        
    // UV�̌v�Z
        element.tex = float2(
        clipRange.x + clipRange.z * offset_UV[i].x,
        clipRange.y + clipRange.w * offset_UV[i].y
        );


        
        output.Append(element);
    }

    output.RestartStrip();
	
}