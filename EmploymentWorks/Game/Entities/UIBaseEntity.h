/*
* �v���C���N���X�@
*/

#pragma once


// �O���錾
class CommonResources;
class UserInterface;

class UIBaseEntity
{
public:
	//���ʃ��\�[�X
	CommonResources* GetCommonResources() { return m_commonResources; }

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
	UIBaseEntity(CommonResources* resources) ;

	//�f�X�g���N�^
	virtual ~UIBaseEntity();

	//������
	virtual void Initialize();
	//�X�V����
	virtual void  Update(const float& elapsedTime);
	//�`��
	virtual void Render();

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�G���e�B�e�B���L�����ǂ����@true:�L��  false:����
	bool m_isEntityActive;
	//�X�V���L�����ǂ����@true:�L��  false:����
	bool m_isUpdateActive;
	//�`�悪�L�����ǂ����@true:�L��  false:����
	bool m_isRenderActive;

};


