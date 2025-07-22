/*
	�N���X��     : Scene
	����         : ���ׂẴV�[���̊��N���X
	�⑫�E���ӓ_ :
*/
#pragma once

class Actor;
class CommonResources;
class RenderManager;
class CollisionManager;
class RigidbodyManager;
class Camera;
class UIManager;

class Scene
{
public:
	//�}�l�[�W���[�̎擾
	RenderManager* GetRenderMangaer() { return m_renderMangaer.get(); }
	CollisionManager* GetCollisionManager() { return m_collisionManager.get(); }
	RigidbodyManager* GetRigidbodyManager() { return m_rigidbodyManager.get(); }
	UIManager* GetUIManager() { return m_uiManager.get(); }

	//�J�����̎擾
	virtual Camera* GetCamera() const = 0;

public:

	// �R���X�g���N�^�A�f�X�g���N�^
	Scene();
	virtual ~Scene();
	// ������
	void Initialize();
	// �h���N���X������
	virtual void SceneInitialize() = 0;
	// �X�V����
	void Update(float deltaTime);
	// �h���N���X�X�V����
	virtual void SceneUpdate(const float& deltaTime) { UNREFERENCED_PARAMETER(deltaTime); };
	// �`�揈��
	void Render();
	virtual void SceneRender() {};
	// �I������
	virtual void Finalize() {};
	
	// �A�N�^�[�폜�t���O���I���ɂ���
	void ActorDestroyOn() { m_isActorDestroy = true; }

public:
	// �A�N�^�[�ǉ�
	template<typename Act , typename...Args>
	Act* AddActor(Args&&... args);
	// �A�N�^�[�폜
	void RemoveActor();


private:
	// �`�F���W�t���O
	bool m_isChangeScene;
	// �Ǘ��A�N�^�[
	std::vector<std::unique_ptr<Actor>> m_actors;
	// �ۗ��A�N�^�[
	std::vector<std::unique_ptr<Actor>> m_holdActors;
	// �A�b�v�f�[�g�m�F�p�t���O
	bool m_updateNow;
	// �A�N�^�[�폜�t���O
	bool m_isActorDestroy;

	// �L�[�{�[�h�X�e�[�g
	DirectX::Keyboard::State m_keyboardState;


	//�`��̃}�l�[�W���[
	std::unique_ptr<RenderManager> m_renderMangaer;
	//�����蔻��̃}�l�[�W���[
	std::unique_ptr<CollisionManager> m_collisionManager;
	//���W�b�g�{�f�B�[�}�l�[�W���[
	std::unique_ptr<RigidbodyManager> m_rigidbodyManager;
	//UI�}�l�[�W���[
	std::unique_ptr<UIManager> m_uiManager;



};

template<typename Act , typename...Args>
inline Act* Scene::AddActor(Args&&...args)
{
	// �A�N�^�[�̐���
	auto actor = std::make_unique<Act>(std::forward<Args>(args)...);
	// �߂�l
	Act* act = actor.get();
	// �A�b�v�f�[�g���̏ꍇ
	if (m_updateNow)
	{
		m_holdActors.push_back(std::move(actor));
	}
	else
	{
		m_actors.push_back(std::move(actor));
	}
	return act;
}

