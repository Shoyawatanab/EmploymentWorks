#pragma once
#include "GameBase/Actor.h"

class Camera;

class Explosiion : public Actor
{
public:
	// �A�j���[�V�����T�C�Y
	static constexpr float ANIMATION_SIZE = 1.0f / 7.0f;	// 7��
	// �A�j���[�V�����̃C���^�[�o���F�t���[���P��
	static constexpr int ANIMATION_INTERVAL = 5;
	//�����̑傫��
	static constexpr DirectX::SimpleMath::Vector2 SCALE {5, 5};


public:
	//�R���X�g���N
	Explosiion(Scene* scene);
	//�f�X�g���N�^
	~Explosiion() override;

	// �R���|�[�l���g�S�̂̍X�V
	void UpdateActor(const float& deltaTime) override;

	//�`�揈��
	void Render(const Camera& camera);

	//�A�N�e�B�u�ɂȂ������ɌĂ΂��֐�
	void OnEnable() override;


private:

	// �|���S���`��p
// �|���S��
	DirectX::VertexPositionTexture m_vertices[4];
	// �x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �r���{�[�h�s��
	DirectX::SimpleMath::Matrix m_billboardMat;

	// �t���[���J�E���^
	int m_frameCounter;
	// �A�j���[�V�����L�[
	int m_animationKey;


};
