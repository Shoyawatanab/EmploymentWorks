/*
	�N���X��     : RenderManager
	����         : �`��}�l�[�W���[
	�⑫�E���ӓ_ : Scene�Ő錾
*/
#pragma once
#include "GameBase/Component/Model/ModelComponent.h"
#include "GameBase/Component/UI/ImageComponent.h"
#include "GameBase/Component/Effect/EffectComponent.h"
#include "GameBase/Component/RoundShadow/RoundShadowComponent.h"
#include "GameBase/Component/Collider/ColliderComponent.h"

class Camera;
class Canvas;

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
	void AddCanvas(Canvas* canvas);
	//UI�̍폜
	void RemoveCanvas(Canvas* canvas);

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
	std::vector<Canvas*> m_canvass;
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