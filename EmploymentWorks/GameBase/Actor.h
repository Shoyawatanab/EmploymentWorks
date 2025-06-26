#pragma once
#include"Component.h"

class Scene;
class Transform;
class ColliderComponent;

class Actor
{
public:
	//�I�u�W�F�N�g�^�O
	enum class ObjectTag
	{
		NONE                               //�ʏ�
		,PLAYER							   //�v���C��
		,PLAYER_PARTS					   //�v���C���p�[�c
		,STAGE							   //�X�e�[�W
		,BOOMERANG						   //�u�[������
		,BOSS_ENEMY						   //�{�X�G
		,BOSS_ENEMY_PARTS				   //�{�X�G�p�[�c
		,BIRD_ENEMY						   //���̓G
		,ENEMY							   //�G
		,BEAM							   //�r�[��
		,BIRD_BULLET                       //���G�̒e								   
	};

public:
	// �V�[���̃Z�b�g
	void SetScene(Scene* scene) { m_scene = scene; }
	//�V�[���̎擾
	Scene* GetScene() const { return m_scene; }
	// �g�����X�t�H�[���擾
	Transform* GetTransform() const { return m_transform; }
	// �A�N�e�B�u�̃Z�b�g�@true: �L���@false:����
	void SetActive(bool active);
	//�A�N�e�B�u�̎擾 true: �L���@false:����
	bool GetActive() const { return m_isActive; }
	// �j��t���O�擾
	bool GetIsDestroy() const { return m_isDestroy; }
	// �R���|�\�l���g�j��t���O
	void ComponentDestroyOn() { m_isComponentDestroy = true; }

	//�I�u�W�F�N�g�^�O�̎擾
	virtual ObjectTag GetObjectTag() { return ObjectTag::NONE; }



public:
	// �R���X�g���N�^
	Actor(Scene* scene);
	// �f�X�g���N�^
	virtual ~Actor();
	// ������
	virtual void Initialize() {};
	// �X�V����
	void Update(const float& deltaTime);
	// �R���|�[�l���g�S�̂̍X�V
	void UpdateComponent(const float& deltaTime);
	// �P�̍X�V
	virtual void UpdateActor(const float& deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };
	// �I������
	virtual void Finalize() {};
	//�A�N�e�B�u�ɂȂ������ɌĂ΂��֐�
	virtual void OnEnable() {};
	//��A�N�e�B�u�ɂȂ������ɌĂ΂��֐�
	virtual void OnDisable() {}
	// �폜
	void Destroy();
	// �R���|�[�l���g�ǉ�
	template<typename Comp , typename ...Args>
	Comp* AddComponent(Args&&...args);
	// �R���|�[�l���g�擾
	template<typename Comp>
	Comp* GetComponent();
	


//Collision�֌W
	//�����������ɌĂяo�����
	virtual void OnCollisionEnter(ColliderComponent* collider) { UNREFERENCED_PARAMETER(collider); };
	//�����葱���Ă���Ƃ��̌Ăяo�����
	virtual void OnCollisionStay(ColliderComponent* collider) { UNREFERENCED_PARAMETER(collider); };
	//�Փ˂��I�������Ƃ��ɌĂяo�����
	virtual void OnCollisionExit(ColliderComponent* collider) { UNREFERENCED_PARAMETER(collider); };


private:
	// �R���|�[�l���g�폜
	void RemoveComponent();

private:
	// �����V�[��
	Scene* m_scene;
	// �Ǘ�����R���|�[�l���g
	std::vector<std::unique_ptr<Component>> m_components;
	// �g�����X�t�H�[��
	Transform* m_transform;
	// �A�N�e�B�u�t���O
	bool m_isActive;
	// �j��t���O
	bool m_isDestroy;
	// �R���|�[�l���g�j��t���O
	bool m_isComponentDestroy;

};

template<typename Comp , typename...Args>
inline Comp* Actor::AddComponent(Args&&...args)
{
	// �R���|�[�l���g�̍쐬
	auto component = std::make_unique<Comp>(std::forward<Args>(args)...);
	// ���^�[���R���|�[�l���g
	Comp * back = component.get();
	// �R���|�[�l���g�Ƀv�b�V���o�b�N����
	m_components.push_back(std::move(component));
	// �R���|�[�l���g��Ԃ�
	return back;

}

template<typename Comp>
inline Comp* Actor::GetComponent()
{
	// �R���|�[�l���g��T��
	for (auto& component : m_components)
	{
		if (typeid(*component) == typeid(Comp))
		{
			Comp* comp = dynamic_cast<Comp*>(component.get());
			return comp;
		}
	}
	return nullptr;
}