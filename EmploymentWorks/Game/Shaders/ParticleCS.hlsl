// �R���X�^���g�o�b�t�@
cbuffer ConstBuffer : register(b0)
{
    matrix matWorld;
    matrix matView;
    matrix matProj;
};

// �o�͐��RWTexture
RWTexture2D<float4> OutputTexture : register(u0);

// �X���b�h�O���[�v�T�C�Y�i16x16�j
[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint width, height;
    OutputTexture.GetDimensions(width, height);

    float2 uv = float2(DTid.xy) / float2(width, height);

    // �F��UV�x�[�X�̃O���f�[�V�����ŏo��
    float4 color = float4(uv.x, uv.y, 1.0 - uv.x, 1.0); // R=U, G=V, B=���]

    OutputTexture[DTid.xy] = float4(1.0f, 1.0f, 1.0f, 1.0f);
    
    
}