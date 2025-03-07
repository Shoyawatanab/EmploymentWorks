#pragma once

//	�O���錾
class CommonResources;

namespace WataLib
{


	/// <summary>
	/// DirectX::Model�̃��b�p�[�N���X
	/// </summary>
	class Model3D
	{
	//	�Q�b�^�[
	public:

		//	���W�̎擾
		const DirectX::SimpleMath::Vector3& GetPosition() const { return m_position; }
		//	�X�P�[���̎擾
		const DirectX::SimpleMath::Vector3& GetScale() const { return m_scale; }
		//	��]�̎擾
		const DirectX::SimpleMath::Quaternion& GetRotate() const { return m_rotate; }

	//	�Z�b�^�[
	public:

		//	���W�̐ݒ�
		void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
		//	�X�P�[���̐ݒ�
		void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
		//	��]�̐ݒ�
		void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//	���J�֐�
	public:

		//	�R���X�g���N�^
		Model3D();
		//	�f�X�g���N�^
		~Model3D() = default;

		//	�J�n�֐�
		void Initialize
		(
			CommonResources* resouce, const wchar_t* szFileName,DirectX::SimpleMath::Vector3 Pos,DirectX::SimpleMath::Vector3 Scale
		);

		//	�`��֐�
		void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);

	//	�����p�����[�^
	private:
		//���f��
		std::unique_ptr<DirectX::Model> m_model;


		DirectX::SimpleMath::Vector3	m_position;	//	���W
		DirectX::SimpleMath::Vector3	m_scale;	//	�X�P�[��
		DirectX::SimpleMath::Quaternion m_rotate;	//	��]

		CommonResources* m_commonResources;

	};
}