#pragma once
#include "Libraries/WataLib/Singleton.h"



class ShaderFactory : public Singleton<ShaderFactory>
{
	friend class Singleton<ShaderFactory>;
public:
	//�R���X�g���N�^
	ShaderFactory() = default;
	//�f�X�g���N�^
	~ShaderFactory() = default;

	//�o�[�e�b�N�X�V�F�[�_�[�̍쐬
	Microsoft::WRL::ComPtr<ID3D11VertexShader> CreateVS(ID3D11Device* device,std::string fileName);
	//�s�N�Z���V�F�[�_�[�̍쐬
	Microsoft::WRL::ComPtr<ID3D11PixelShader> CreatePS(ID3D11Device* device, std::string fileName);
	//�W�I���g���b�N�V�F�[�_�[�̍쐬
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> CreateGS(ID3D11Device* device, std::string fileName);
	//�C���v�b�g���C�A�E�g�̍쐬
	Microsoft::WRL::ComPtr<ID3D11InputLayout> CreateInputLayout(ID3D11Device* device, const std::vector<D3D11_INPUT_ELEMENT_DESC> layout, std::string fileName);

private:

	


};
