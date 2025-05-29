/*
* �v���C���N���X�@
*/

#pragma once


// �O���錾
class CommonResources;

class BaseEntity
{
public:
	//���ʃ��\�[�X
	CommonResources* GetCommonResources() { return m_commonResources; }
	//ID�̎擾
	 int GetID() const { return m_id; }

	 static int GetNextID() { return m_nextId; };

	//���W�̎擾
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position ; };
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
	//���x�̎擾
	const DirectX::SimpleMath::Vector3& GetVelocity() { return m_velocity; }
	//���x�̓o�^
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	//�d�ʂ��L�����ǂ����@true:�L��  false:����
	const bool GetIsGravity() { return m_isGravity; }
	//�d�͂��L�����̓o�^ true:�L��  false:����
	void SetIsGravity(const bool& enabled) { m_isGravity = enabled; }

	//�e�̎擾
	BaseEntity* GetParent() { return m_parent; }
	//�e�̓o�^
	void SetParent(BaseEntity* parent);
	//�e�����邩�ǂ����@true:����  false:�Ȃ�
	bool GetIsParent() { return m_isParent; }


	//�I�u�W�F�N�g���L�����ǂ����̓o�^�@true:�L��  false:����
	void SetIsEntityActive(const bool& isActive) { m_isEntityActive = isActive;  if(m_isEntityActive)OnEnable(); else OnDisable(); }
	//�I�u�W�F�N�g���L�����ǂ����̎擾�@true:�L��  false:����
	const bool& GetIsEntityActive() { return m_isEntityActive; }

	//�X�V���L�����ǂ����̓o�^�@true:�L��  false:����
	void SetIsUpdateActive(const bool& isActive) { m_isUpdateActive = isActive; }
	//�X�V���L�����ǂ����̎擾�@true:�L��  false:����
	const bool& GetIsUpdateActive() { return m_isUpdateActive; }

	//�`�悪�L�����ǂ����̓o�^�@true:�L��  false:����
	void SetIsRenderActive(const bool& isActive) { m_isRenderActive = isActive; }
	//�`�悪�L�����ǂ����̎擾�@true:�L��  false:����
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
	//�G���e�B�e�B���L�����ǂ����@true:�L��  false:����
	bool m_isEntityActive;
	//�X�V���L�����ǂ����@true:�L��  false:����
	bool m_isUpdateActive;
	//�`�悪�L�����ǂ����@true:�L��  false:����
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
	//�e�����邩�ǂ���
	bool m_isParent;

	//���[�J�����W
	DirectX::SimpleMath::Vector3 m_localPosition;
	//���[�J���傫��
	DirectX::SimpleMath::Vector3 m_localScale;
	//���[�J����]
	DirectX::SimpleMath::Quaternion m_localRotation;
	//���[�J���s��
	DirectX::SimpleMath::Matrix m_localMatrix;
	//�d�͂����邩�ǂ���
	bool m_isGravity;
	//���x
	DirectX::SimpleMath::Vector3 m_velocity;
	//�d��
	float m_gravity;

};


