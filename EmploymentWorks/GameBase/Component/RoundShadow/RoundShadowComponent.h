#pragma once
#include "GameBase/Component.h"
#include "GameBase/Component/Components.h"


class RoundShadowComponent : public Component
{
public:
	//�R���X�g���N�^
	RoundShadowComponent(Actor* owner,float radius);
	//�f�X�g���N�^
	~RoundShadowComponent() override;

	//�`��
	void Render(const Camera& camera);

private:

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;

	// �x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �[�x�X�e���V���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	//���a
	float m_radius;


};