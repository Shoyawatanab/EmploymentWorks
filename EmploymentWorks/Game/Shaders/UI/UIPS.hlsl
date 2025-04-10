#include "UI.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//	�w�肳�ꂽ�摜�̕\��
    float4 output = tex.Sample(samLinear, input.tex);

	//	�Q�[�W�̌��ݒl����A���[�^�[�p�摜�����x�����ʒu�Ń��O���f�[�V�����ƂȂ�ɂ́A
	//	�ǂ̂悤�Ȓl���usmoothValue�v�ɑ������΂������낤�H
	//	�q���g�F��̒l���������OK�B�v�Z���܂ŏ����K�v���Ȃ��I
    float4 smoothValue = input.color;
    output.a *= lerp(1.0f, 0.0f, smoothstep(smoothValue, smoothValue + 0.01f, input.tex.x)); //tex.y�ŏ㉺�Ɉړ��\

    //�S�̂̓����x��������
    output *= diffuse;

    return output;
    
}