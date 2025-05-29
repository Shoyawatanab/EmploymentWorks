/*
	@file	BirdEnemyBeamEnergyBall.h
	@brief�@���̓G�̃r�[���̃G�l���M�[�e
*/
#pragma once
#include "Game/Entities/MoveEntity.h"

// �O���錾
class CommonResources;
class BirdEnemyBeam;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}
namespace WataLib
{
	class Bounding;
}


class BirdEnemyBeamEnergyBall : public CollisionEntity
{


public:
	//�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//�R���X�^���g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
	};

	static constexpr float SPHERE_COLLIDER_SIZE = 1.0f;
	static constexpr DirectX::SimpleMath::Vector3  BOX_COLLIDER_SIZE {0.5f,0.5f,0.5f};
	
public:


	//�^�[�Q�b�g�̎擾
	const DirectX::SimpleMath::Vector3& GetTarget() { return m_target; }
	//�^�[�Q�b�g�̓o�^
	void SetTarget(const DirectX::SimpleMath::Vector3& target) { m_target = target; }
	//�����̑傫���̎擾
	const DirectX::SimpleMath::Vector3& GetInitialScale() { return m_initialScale; }
	//�ő�T�C�Y�̎擾
	const DirectX::SimpleMath::Vector3& GetMaxScale() { return m_maxScale; }
	//�ő�T�C�Y�̎��Ԃ̎擾
	float GetMaxSizeTime() const { return m_maxSizeTime; }


public :
	//�R���X�g���N�^
	BirdEnemyBeamEnergyBall(CommonResources* resources
		, BaseEntity* parent
		, BirdEnemyBeam* beam);

	//�f�X�g���N�^
	~BirdEnemyBeamEnergyBall() override;

	
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
	const bool GetIsExtrusion() override { return true; };
	//�����蔻����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::ENEMY}
		};
	}

	//�����o�����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};


private:


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
	//
	DirectX::SimpleMath::Vector3 m_iniialPosition;
	//
	DirectX::SimpleMath::Quaternion m_initialRotate;
	//
	DirectX::SimpleMath::Vector3 m_target;
	//
	DirectX::SimpleMath::Vector3 m_initialScale;
	//
	DirectX::SimpleMath::Vector3 m_maxScale;
	//
	DirectX::SimpleMath::Vector3 m_wordlPosition;
	//
	BirdEnemyBeam* m_beam;
	//
	float m_maxSizeTime;
	//
	float m_time;



};
