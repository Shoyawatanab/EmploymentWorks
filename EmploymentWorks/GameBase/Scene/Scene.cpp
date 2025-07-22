/*
	�N���X��     : Scene
	����         : ���ׂẴV�[���̊��N���X
	�⑫�E���ӓ_ :
*/
#include"pch.h"
#include"Scene.h"
#include"GameBase/Actor.h"
#include "GameBase/Managers.h"
#include "GameBase/Camera/Camera.h"
#include "GameBase/Messenger/InputMessenger.h"


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
	,m_keyboardState{}
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
	//�h���N���X�̏�����
	SceneInitialize();

	// �ώ@�҃��X�g���\�[�g����
	InputMessenger::GetInstance()->SortObserverList();
	//  �L�[�͈̓��X�g�𐶐�����
	InputMessenger::GetInstance()->CreateKeyRangeList();

}


// �L�[�{�[�h����������ꂽ�ǂ����𔻒肷��
inline bool IsKeyPress(DirectX::Keyboard::State& state)
{
	// �L�[�{�[�h�X�e�[�g�ւ̃|�C���^���擾����
	auto ptr = reinterpret_cast<uint32_t*>(&state);
	for (int key = 0; key < 0xff; key++)
	{
		const unsigned int buffer = 1u << (key & 0x1f);
		// �L�[����������ꂽ���ǂ����𒲂ׂ�
		if (ptr[(key >> 5)] && buffer)	 return true;
	}
	// �L�[�͉��������Ă��Ȃ�
	return false;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Scene::Update(float deltaTime)
{
	// �L�[�{�[�h�̏�Ԃ��擾����
	m_keyboardState = DirectX::Keyboard::Get().GetState();

	// �L�[�{�[�h�����������ꍇ�Ƀ��b�Z���W���[�ɃL�[�{�[�h�X�e�[�g�ƃv���C���[�m�[�h�ԍ��z���ʒm����
	if (IsKeyPress(m_keyboardState))
	{
		InputMessenger::GetInstance()-> Notify(m_keyboardState);
	}



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





