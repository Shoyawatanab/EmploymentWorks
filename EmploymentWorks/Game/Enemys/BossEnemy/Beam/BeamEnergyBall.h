/*
	@file	BeamEnergyBall.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Entities/MoveEntity.h"

// �O���錾
class CommonResources;
class Beam;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class Bounding;

}

class BeamEnergyBall : public MoveEntity
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

	static constexpr DirectX::SimpleMath::Vector3 INITALPOSITION { 100, 100, 0 };


public:
	//�R���X�g���N
	BeamEnergyBall(CommonResources* resources,BaseEntity* parent);
	
	//�f�X�g���N�^
	~BeamEnergyBall() override;

	
	//������
	void Initialize() override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

	//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::BEAM; };
	//�����蔻��N���X�ɓo�^
	void  AddCollision(CollisionManager* collsionManager) override;

	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//�����蔻��̎�ނ̎擾
	const CollisionType GetCollisionType() override { return CollisionType::AABB; }
	//�����o�������邩�ǂ���
	const bool GetIsExtrusion() override { return false; };
	//�����蔻����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::PLAYERPARTS}
			,{CollisionTag::BOOMERANG}
			,{CollisionTag::ENEMY}
			,{CollisionTag::ENEYPARTS}
		};
	}

	//�����o�����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void AddPointer(Beam* beam);
	//���Z�b�g
	void ReSet();

private:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//	���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;



	// ���f��
	DirectX::Model* m_model;
	//������]
	DirectX::SimpleMath::Quaternion m_initialRotate;
	//�^�[�Q�b�g
	DirectX::SimpleMath::Vector3 m_target;
	//�����T�C�Y
	DirectX::SimpleMath::Vector3 m_initialScale;
	//�ő�T�C�Y
	DirectX::SimpleMath::Vector3 m_maxScale;
	//�r�[��
	Beam* m_beam;
	//�ő�T�C�Y�ɂȂ鎞��
	float m_maxSizeTime;
	//����
	float m_time;




};
