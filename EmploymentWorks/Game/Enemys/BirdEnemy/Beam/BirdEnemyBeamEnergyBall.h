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

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
	};


public:



	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }
 
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }




	DirectX::SimpleMath::Vector3 GetInitialScale() { return m_initialScale; }
	
	DirectX::SimpleMath::Vector3 GetMaxScale() { return m_maxScale; }

	float GetMaxSizeTime() { return m_maxSizeTime; }


public :
	BirdEnemyBeamEnergyBall(CommonResources* resources, BaseEntity* parent, BirdEnemyBeam* beam);

	//�f�X�g���N�^
	~BirdEnemyBeamEnergyBall() override;

	//IObject
		//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

	//ICollisionObject
		//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Beam; };
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
			{CollisionTag::Enemy}
		};
	}




private:


	//	���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_iniialPosition;
	DirectX::SimpleMath::Quaternion m_initialRotate;
	DirectX::SimpleMath::Vector3 m_target;
	DirectX::SimpleMath::Vector3 m_initialScale;
	DirectX::SimpleMath::Vector3 m_maxScale;
	DirectX::SimpleMath::Vector3 m_wordlPosition;

	BirdEnemyBeam* m_beam;

	float m_maxSizeTime;
	float m_time;



};
