#include "Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	�w�肳�ꂽ�摜��������擾
	float4 output = tex.Sample(samLinear, input.Tex);

	//�����x
	output.a *= diffuse.a;
    
	
	//	C++����w�肳�ꂽ�F�������l�����āA�\���F������
	return output;
}