#include"pch.h"
#include"Scene.h"
#include"GameBase/Actor.h"
#include "GameBase/Managers.h"
#include "GameBase/Camera/Camera.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Scene::Scene()
	:
	m_actors{}
	,m_holdActors{}
	,m_updateNow{false}
	,m_isChangeScene{}
	,m_isActorDestroy{false}
{

	m_renderMangaer = std::make_unique<RenderManager>();

	m_collisionManager = std::make_unique<CollisionManager>();

	m_rigidbodyManager = std::make_unique<RigidbodyManager> ();

	m_uiManager = std::make_unique<UIManager>();


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Scene::~Scene()
{
	for (auto& actor : m_actors)
	{
		actor->Finalize();
	}

	m_actors.clear();

	m_holdActors.clear();

}

/// <summary>
/// ����������
/// </summary>
void Scene::Initialize()
{
	for (auto& actor : m_actors)
	{
		actor->Initialize();
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Scene::Update(float deltaTime)
{
	



	//�X�V�t���O��true�ɕύX
	m_updateNow = true;
	// �A�N�^�[�̍X�V������
	for (auto& actor : m_actors)
	{
		if (!actor->GetActive()) { continue; }
		actor->Update(deltaTime);
	}

	SceneUpdate(deltaTime);


	// �V�[���ʂ̍X�V
	m_updateNow = false;

	m_rigidbodyManager->Update(deltaTime);

	m_collisionManager->Update(deltaTime);

	GetCamera()->Update(deltaTime);

	m_uiManager->Update(deltaTime);

	// �ۗ��I�u�W�F�N�g���X�V�I�u�W�F�N�g��
	std::move(m_holdActors.begin(), m_holdActors.end(), std::back_inserter(m_actors));
	m_holdActors.clear();
	// �A�N�^�[�̍폜
	RemoveActor();

}

/// <summary>
/// �`�揈��
/// </summary>
void Scene::Render()
{
	
	m_renderMangaer->Render(*GetCamera());
	
	// �V�[���̕`��
	SceneRender();

}

/// <summary>
/// �A�N�^�[�̍폜
/// </summary>
void Scene::RemoveActor()
{
	// �폜�v�����Ȃ��Ȃ�Ԃ�
	if (!m_isActorDestroy) { return; }
	// �폜�v�f���폜
	m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [&](
		std::unique_ptr<Actor>& actor) {
			return actor->GetIsDestroy();
		}), m_actors.end());
	// �폜�v���t���O���I�t��
	m_isActorDestroy = false;
}