/*
* �v���C���N���X�@
*/

#pragma once


// �O���錾
class CommonResources;

class BaseEntity
{
public:

	CommonResources* GetCommonResources() { return m_commonResources; }

	 int GetID() const { return m_id; }

	 static int GetNextID() { return m_nextId; };

	//���W�̎擾
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position  ; };
	//���W�̐ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& position) 
	{ 
		m_position = position;  
		if (!m_parent) { m_localPosition = position; }; 
	};
	//�傫���̎擾
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; };
	//�傫���̐ݒ�
	void SetScale(const DirectX::SimpleMath::Vector3& scale) 
	{ 
		m_scale = scale; 
		if (!m_parent) { m_localScale = scale; };

	};

	//��]�̎擾
	const DirectX::SimpleMath::Quaternion& GetRotation() { return m_rotation; };
	//��]�̐ݒ�
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation) 
	{ 
		m_rotation = rotation; 
		if (!m_parent) { m_rotation = rotation; };

	};
	//�s��̎擾
	const DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; };
	//�s��̐ݒ�
	void SetWorldMatrix(const DirectX::SimpleMath::Matrix& matrix) 
	{ 
		m_worldMatrix = matrix;
		if(!m_parent) { m_localMatrix = matrix; };

	}

	//���[�J�����W�̎擾
	const DirectX::SimpleMath::Vector3& GetLocalPosition() { return m_parent ? m_localPosition : m_position; };
	//���[�J�����W�̐ݒ�
	void SetLocalPosition(const DirectX::SimpleMath::Vector3& position) { m_parent  ? m_localPosition = position : m_position = position; };
	//���[�J���傫���̎擾
	const DirectX::SimpleMath::Vector3& GetLocalScale() { return m_parent ? m_localScale : m_scale; };
	//���[�J���傫���̐ݒ�
	void SetLocalScale(const DirectX::SimpleMath::Vector3& scale) { m_parent  ? m_localScale = scale : m_scale = scale  ; };
	//���[�J����]�̎擾
	const DirectX::SimpleMath::Quaternion& GetLocalRotation() { return m_parent  ? m_localRotation : m_rotation; };
	//���[�J����]�̐ݒ�
	void SetLocalRotation(const DirectX::SimpleMath::Quaternion& rotation) { m_parent  ? m_localRotation = rotation :m_rotation = rotation ; };
	
	//�e�̎擾
	BaseEntity* GetParent() { return m_parent; }

	//�e�̓o�^
	void SetParent(BaseEntity* parent);

	//�I�u�W�F�N�g���L�����ǂ����̓o�^
	void SetIsEntityActive(const bool& isActive) { m_isEntityActive = isActive;  if(m_isEntityActive)OnEnable(); else OnDisable(); }
	//�I�u�W�F�N�g���L�����ǂ����̎擾
	const bool& GetIsEntityActive() { return m_isEntityActive; }

	//�X�V���L�����ǂ����̓o�^
	void SetIsUpdateActive(const bool& isActive) { m_isUpdateActive = isActive; }
	//�X�V���L�����ǂ����̎擾
	const bool& GetIsUpdateActive() { return m_isUpdateActive; }

	//�`�悪�L�����ǂ����̓o�^
	void SetIsRenderActive(const bool& isActive) { m_isRenderActive = isActive; }
	//�`�悪�L�����ǂ����̎擾
	const bool& GetIsRenderActive() { return m_isRenderActive; }
	//�L���ɂȂ�����
	virtual void OnEnable()  {};
	//�����ɂȂ�����
	virtual void OnDisable() {};

public:
	//�R���X�g���N�^
	BaseEntity(CommonResources* resources,
				const DirectX::SimpleMath::Vector3&    scale, 
		        const DirectX::SimpleMath::Vector3&    position,
		        const DirectX::SimpleMath::Quaternion& rotation) ;

	//�f�X�g���N�^
	virtual ~BaseEntity();

	//������
	virtual void Initialize();
	//�X�V����
	virtual void  Update(const float& elapsedTime);
	//�`��
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//id
	int m_id;

	static int m_nextId;

	bool m_isEntityActive;

	bool m_isUpdateActive;

	bool m_isRenderActive;

	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//��]
	DirectX::SimpleMath::Quaternion m_rotation;
	//�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;

	//�e�N���X
	BaseEntity* m_parent;
	//���[�J�����W
	DirectX::SimpleMath::Vector3 m_localPosition;
	//���[�J���傫��
	DirectX::SimpleMath::Vector3 m_localScale;
	//���[�J����]
	DirectX::SimpleMath::Quaternion m_localRotation;
	//���[�J���s��
	DirectX::SimpleMath::Matrix m_localMatrix;

};


