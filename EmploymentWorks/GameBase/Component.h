#pragma once
class Scene;
class Actor;

class Component
{
public:
	// �A�N�^�[�̎擾
	Actor* GetActor() const { return m_actor; }
	// �A�N�e�B�u�t���O
	void SetActive(bool isActive) { m_isActive = isActive; }
	bool GetActive() const { return m_isActive; }
	// �I�[�_�[�擾
	int GetUpdateOrder() const { return m_updateOrder; }
	// �j��t���O�擾
	bool GetIsDestroy() const { return m_isDestroy; }
public:
	// �R���X�g���N�^
	Component(Actor* owner, int updateOrder = 0);
	// �f�X�g���N�^
	virtual ~Component();
	// �A�b�v�f�[�g
	virtual void Update(const float& deltaTime);
	// �폜
	void Destroy();

private:
	// �����A�N�^�[
	Actor* m_actor;
	// �A�N�e�B�u�t���O
	bool m_isActive;
	// �j��t���O
	bool m_isDestroy;
	// �X�V�I�[�_�[
	int m_updateOrder;
};