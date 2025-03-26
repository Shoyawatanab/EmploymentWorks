#include "pch.h"
#include "GameEndUI.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Libraries/WataLib/DrawTexture.h"
#include "Game/Scene/PlayScene.h"
#include "Libraries/WataLib/UserInterface.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameEndUI::GameEndUI()
	:
	m_commonResources{}
	,m_position{}
	,m_scale{}
	,m_rotation{}
	,m_player{}
	,m_windowSize{}
	, m_clearBackGraund{}
	,m_overBackGraund{}
	,m_titleUI{}
	, m_reTryUI{}
	,m_animationTime{}
	,m_state{}
	,m_backGraund{}
	,m_enemyAnimationTime{}
	,m_playScene{}
{

	m_clearBackGraund = std::make_unique<UserInterface>();
	m_overBackGraund = std::make_unique<UserInterface>();
	m_titleUI = std::make_unique<UserInterface>();
	m_reTryUI = std::make_unique<UserInterface>();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameEndUI::~GameEndUI()
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void GameEndUI::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{


	m_backGraund->Render();
	m_titleUI->Render();
	m_reTryUI->Render();

	if (m_animationTime < MAXANIMATIONTIME)
	{
		return;
	}

	for (auto& texture : m_textures)
	{
		texture->Render();
	}

	m_arrow->Render();

	
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="playScene">�v���C�V�[��</param>
void GameEndUI::AddPointer(Player* player, PlayScene* playScene)
{
	m_player = player;
	m_playScene = playScene;
}

//�摜�̓ǂݍ��݂Ɛ���
void GameEndUI::CreateTexture()
{

	m_clearBackGraund->Create(
		m_commonResources->GetDeviceResources(), L"Resources/Textures/ClearBackGraund.png"
		, CENTERPOSITION, Vector2::Zero
	);	
	m_overBackGraund->Create(
		m_commonResources->GetDeviceResources(), L"Resources/Textures/GameOver.png"
		, CENTERPOSITION, Vector2::Zero
	);
	m_titleUI->Create(
		m_commonResources->GetDeviceResources(), L"Resources/Textures/ClearTitleTex.png"
		, CENTERPOSITION, Vector2::Zero
	);

	m_reTryUI->Create(
		m_commonResources->GetDeviceResources(), L"Resources/Textures/ClearReTryTex.png"
		, CENTERPOSITION, Vector2::Zero
	);

}

/// <summary>
/// �|�b�v�A�b�v�A�j���[�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void GameEndUI::Animation(const float& elapsedTime)
{
	//���������߂�
	float ratio = m_animationTime / MAXANIMATIONTIME;

	ratio = std::min(ratio, 1.0f);

	Vector2 position;
	Vector2 scale;
	//�傫�������߂�
	scale = Vector2::Lerp(Vector2::Zero, ENDSCSLE, ratio);
	m_backGraund->SetScale(scale);
	m_titleUI->SetScale(scale);
	m_reTryUI->SetScale(scale);

	//�w�i
	position = Vector2::Lerp(CENTERPOSITION, BACKGRAUNDENDPOSITION, ratio);
	m_backGraund->SetPosition(position);
	//�^�C�g��UI
	position = Vector2::Lerp(CENTERPOSITION, TITLEUIENDPOSITION, ratio);
	m_titleUI->SetPosition(position);
	//���g���CUI
	position = Vector2::Lerp(CENTERPOSITION, RETRYUIENDPOSITION, ratio);
	m_reTryUI->SetPosition(position);

	m_animationTime += elapsedTime;

}



/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void GameEndUI::Initialize(CommonResources* resources)
{
	m_commonResources = resources;

	//��ʃT�C�Y�̎擾
	m_windowSize.first = m_commonResources->GetDeviceResources()->GetOutputSize().right;
	m_windowSize.second = m_commonResources->GetDeviceResources()->GetOutputSize().bottom;

	CreateTexture();

	m_state = State::ReTry;

	m_backGraund = m_clearBackGraund.get();


	auto texture = std::make_unique<UserInterface>();
	texture->Create(
		m_commonResources->GetDeviceResources(), L"Resources/Textures/ChangeUI.png", DirectX::SimpleMath::Vector2(200, 650), Vector2(0.4f, 0.4f)
	);

	m_textures.push_back(std::move(texture));


	texture = std::make_unique<UserInterface>();
	texture->Create(
		m_commonResources->GetDeviceResources(), L"Resources/Textures/DecisionUI.png", DirectX::SimpleMath::Vector2(570, 650), Vector2(0.4f, 0.4f)
	);

	m_textures.push_back(std::move(texture));


	m_arrow = std::make_unique<UserInterface>();

	m_arrow->Create(m_commonResources->GetDeviceResources(), L"Resources/Textures/Arrow.png", DirectX::SimpleMath::Vector2(450, 360), Vector2(0.2f, 0.2f));



}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void GameEndUI::Update(const float& elapsedTime)
{

	if (m_enemyAnimationTime < ENEMYANIMATIONTIME)
	{
		m_enemyAnimationTime += elapsedTime;
		return;
	}

	Animation(elapsedTime);

	if (m_animationTime < MAXANIMATIONTIME)
	{
		return;
	}
	
	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.W)
	{
		m_state = State::ReTry;
		m_arrow->SetPosition(DirectX::SimpleMath::Vector2(450, 360));

	}
	else if (kbTracker->released.S)
	{
		m_state = State::Title;
		m_arrow->SetPosition(DirectX::SimpleMath::Vector2(450, 500));
	}

	switch (m_state)
	{
		case GameEndUI::State::Title:
			m_reTryUI->SetScale(m_reTryUI->GetInialScale());
			m_titleUI->SetScale(m_titleUI->GetInialScale() * EXPANSION);

			break;
		case GameEndUI::State::ReTry:
			m_reTryUI->SetScale(m_reTryUI->GetInialScale() * EXPANSION);
			m_titleUI->SetScale(m_titleUI->GetInialScale());

			break;
		default:
			break;
	}

	if (kbTracker->released.Space)
	{
		switch (m_state)
		{
			case GameEndUI::State::Title:
				m_playScene->SetNextSceneID(PlayScene::SceneID::TITLE);
				break;
			case GameEndUI::State::ReTry:
				m_playScene->SetNextSceneID(PlayScene::SceneID::PLAY);
				break;
			default:
				break;
		}


	}

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void GameEndUI::Enter()
{



}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void GameEndUI::Exit()
{
}




