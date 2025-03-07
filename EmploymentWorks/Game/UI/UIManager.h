#pragma once
/*
	@file	UIManager.h.h
	@brief	�G�̊Ǘ��N���X
*/
#pragma once
#include "pch.h"
#include "Game/Interface/ICharacter.h"
#include "Game/Interface/IObserver.h"

// �O���錾
class CommonResources;
class UIStateMachine;
class Player;
class PlayScene;
class EnemyManager;

class UIManager :  public IObserver
{
public:
	//�R���X�g���N�^
	UIManager();
	//�f�X�g���N�^
	~UIManager() ;
	//������
	void Initialize(CommonResources* resources);
	//�X�V����
	void Update(const float& elapsedTime);
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	//
	void Finalize() ;

	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(Player* player , PlayScene* playScene, EnemyManager* enemyManager);

	//IObserver
//�ʒm���ɌĂ΂��֐�
	void Notify(EventParams::EventType type, void* datas)  override;

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//
	std::unique_ptr<UIStateMachine> m_stateMahine;

};
