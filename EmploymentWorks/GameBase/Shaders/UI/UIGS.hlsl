#include "UI.hlsli"

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

        float2 window = windowSize.xy;

    // �X�N���[�����W�����ꂽ�|�W�V����
        float2 Position = input[0].pos.xy / window * 2.0f;
        Position = float2(center.x + Position.x, center.y - Position.y);

    // ���[�J�����W���` [-0.5, 0.5] �� �X�P�[�����O�i�摜�T�C�Y�j
        float2 local = offset_array[i].xy * size.xy;

    // ��]
        float2 rotated;
        rotated.x = local.x * cosA - local.y * sinA;
        rotated.y = local.x * sinA + local.y * cosA;

    // �r���[�g��k��
        rotated *= viewRange.xy;

    // �ŏI���W���X�N���[����ɕϊ�
        float2 final = rotated / window * 2.0f;
        element.pos.xy = Position + final;
        element.pos.z = 0.0f;
        element.pos.w = 1.0f;

    // UV�͂��̂܂܂�OK
        element.tex = float2(
        clipRange.x + clipRange.z * offset_UV[i].x,
        clipRange.y + clipRange.w * offset_UV[i].y
    );

        output.Append(element);
    }

    output.RestartStrip();
	
}