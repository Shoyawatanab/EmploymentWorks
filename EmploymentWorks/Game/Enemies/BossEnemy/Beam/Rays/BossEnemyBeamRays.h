#pragma once
#include "GameBase/Actor.h"


class Camera;
class ModelComponent;

class BossEnemyBeamRays : public Actor
{
public:
	//�R���X�^���g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    Color;

	};

public:
	//�R���X�g���N
	BossEnemyBeamRays(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyBeamRays();

private:
	//���g�`��
	void ModelRender(const Camera& camera);
	//�O�g�`��
	void OutSideModelRender(const Camera& camera);
	//�V�F�[�_�[�쐬
	void CreateShader();

private:
	//�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//	���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;


	//���f���R���|�[�l���g
	ModelComponent* m_outSidemodel;
	ModelComponent* m_model;


};


