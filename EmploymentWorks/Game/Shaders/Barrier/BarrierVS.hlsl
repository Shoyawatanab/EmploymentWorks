#include "Barrier.hlsli"

PS_INPUT main( VS_INPUT input ) 
{
	PS_INPUT output = (PS_INPUT)0;

    output.Pos = mul(float4(input.Pos, 1), matWorld);
    output.Pos = mul(output.Pos, matView);
    output.Pos = mul(output.Pos, matProj);
    
    
	//UV���W�͂��̂܂ܓn��
    output.Tex = input.Tex;
	//���̃V�F�[�_�֏���n��
	return output;
    
}