/*
	@file	CollisionMesh.h
	@brief	Obj�`���̃��b�V�����R���W�����ɂ���N���X
*/
#pragma once

namespace mylib
{
	class CollisionMesh
	{
	private:
		// �O�p�`�|���S����\������\����
		struct Triangle
		{
			DirectX::SimpleMath::Vector3 triangle[3];	// ���_���W
			DirectX::SimpleMath::Vector3 normal;		// �@��

			Triangle(
				DirectX::SimpleMath::Vector3 a,
				DirectX::SimpleMath::Vector3 b,
				DirectX::SimpleMath::Vector3 c
			)
			{
				// �|���S��
				triangle[0] = a;
				triangle[1] = b;
				triangle[2] = c;

				// �@��
				DirectX::SimpleMath::Vector3 ab = triangle[1] - triangle[0];
				DirectX::SimpleMath::Vector3 ac = triangle[2] - triangle[0];
				normal = ab.Cross(ac);	// �E����W�n�Ń|���S���̒��_�������v���̎�

				// ���ӁI
				// normal = ab.Cross(ac) * (-1);	// �E����W�n�Ń|���S���̒��_�����v���̎�
				// obj�f�[�^�̒��_���͔����v���Œ�`����Ă���
			}
		};


	private:
		// ���W�A��]�A�傫���A���_���z��A���_�C���f�b�N�X�z��A�|���S���z��
		DirectX::SimpleMath::Vector3 m_position;
		DirectX::SimpleMath::Quaternion m_rotation;
		float m_scale;
		std::vector<DirectX::VertexPosition> m_vertices;
		std::vector<uint16_t> m_indices;
		std::vector<Triangle> m_triangles;

		// ���b�V���`��p�I�u�W�F�N�g
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPosition>> m_primitiveBatch;


	public:
		CollisionMesh();
		~CollisionMesh() = default;

		// ���b�V���I�u�W�F�N�g���쐬����
		void Initialize(
			ID3D11Device* device,
			ID3D11DeviceContext* context,
			const std::wstring& objName,
			DirectX::SimpleMath::Vector3 position,
			float scale
		);

		// ���b�V���f�[�^�����C���[�t���[���ŕ`�悷��
		void Draw(
			ID3D11DeviceContext* context,
			DirectX::CommonStates* states,
			const DirectX::SimpleMath::Matrix& view,
			const DirectX::SimpleMath::Matrix& projection
		);

		// ���b�V����Ray�Ƃ̏Փ˔���
		bool IntersectRay(
			const DirectX::SimpleMath::Ray& ray,
			DirectX::SimpleMath::Vector3* hitPosition
		);

	private:
		// Obj�t�@�C�������[�h����
		void LoadObjFile(const std::wstring& objName);

		// �|���S�������z��ɓo�^����
		void AddTriangle(
			DirectX::SimpleMath::Vector3 a,
			DirectX::SimpleMath::Vector3 b,
			DirectX::SimpleMath::Vector3 c
		);

	public:
		// �Փ˂����|���S���̒��_����Ԃ�
		std::vector<DirectX::SimpleMath::Vector3> GetHitPolygon(unsigned int hitPolygonNo);
	};
}