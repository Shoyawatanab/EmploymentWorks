#pragma once
#include "GameBase/Component/Components.h"

class Camera;

class RenderManager
{
	
public:

	//�R���X�g���N�^
	RenderManager();
	//�f�X�g���N�^
	~RenderManager();

	//�`�揈��
	void Render(const Camera& camera);
	//���f���̒ǉ�
	void AddModel(ModelComponent* comp);
	//���f���̍폜
	void RemoveModel(ModelComponent* comp);
	//UI�̒ǉ�
	void AddUserInterface(ImageComponent* comp);
	//UI�̍폜
	void RemoveUserInterface(ImageComponent* comp);

	//�R���C�_�[�̒ǉ��@�f�o�b�O�@
	void AddCollider(ColliderComponent* comp);

	//�G�t�F�N�g�̒ǉ�
	void AddEffect(EffectComponent* comp);
	//�ۉe�̒ǉ�
	void AddRoundShadow(RoundShadowComponent* comp);


private:
	//���f���R���|�[�l���g
	std::vector<ModelComponent*> m_models;
	//UI�R���|�[�l���g
	std::vector<ImageComponent*> m_uis;
	//�G�t�F�N�g�R���|�[�l���g
	std::vector<EffectComponent*> m_effects;
	//�ۉe
	std::vector<RoundShadowComponent*> m_roundShadow;

	//�f�o�b�O�@
	//�����蔻��
	std::vector<ColliderComponent*> m_colliders;
	//�x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout;
	//�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;

	

};