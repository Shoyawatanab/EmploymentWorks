// �|�C���g�X�v���C�g �C���X�^���V���O�p�s�N�Z���V�F�[�_�[

// �萔�o�b�t�@
cbuffer ConstantBuffer : register(b0)
{
    matrix View;
    matrix Projection;
    float4 CameraRight;
    float4 CameraUp;
    float4 GlobalColor;
};

// �e�N�X�`���ƃT���v���[
Texture2D DiffuseTexture : register(t0);
SamplerState DiffuseSampler : register(s0);

// ���͍\���́i���_�V�F�[�_�[����̏o�́j
struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
    float2 TexCoord : TEXCOORD0;
    float4 AtlasCoord : TEXCOORD1;
};

// �o�͍\����
struct PS_OUTPUT
{
    float4 Color : SV_TARGET;
};

PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    
    // �e�N�X�`���A�g���X���W���g�p���ăe�N�X�`�����T���v�����O
    float4 texColor = DiffuseTexture.Sample(DiffuseSampler, input.AtlasCoord.xy);
    
    // ���_�J���[�ƃe�N�X�`���J���[������
    output.Color = texColor * input.Color * GlobalColor;
    
    // �A���t�@�e�X�g�i���S�ɓ����ȃs�N�Z���͔j���j
    if (output.Color.a < 0.01f)
    {
        discard;
    }
    
    return output;
}