/*
	@file	GameCameraManager.h
	@brief	TPS�J�����N���X
*/
#pragma once
#include "Game/Interface/ICamera.h"
#include "Game/Interface/IObserver.h"


class Player;
class EnemyManager;

namespace WataLib
{
	class TPS_Camera;
	class GameEndCamera;
}

namespace WataLib
{
	class CameraManager : public IObserver<GameMessageType>
	{
	public:
		//�r���[�s��̎擾
		const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_currentState->GetViewMatrix(); }
		
		ICamera* GetGameCameraState() { return m_currentState; }

		WataLib::TPS_Camera* GetTPSCamera() { return m_tpsCamera.get(); }

		WataLib::GameEndCamera* GetEndCamera() { return m_endCamera.get(); }

		

	public:
		// �R���X�g���N�^
		CameraManager();

		// �f�X�g���N�^
		~CameraManager();
		//������
		void Initialize(CommonResources* resources);

		// �X�V����
		void Update(float elapsedTime);
		//�J�����̐؂�ւ�
		void ChangeState(ICamera* nestState);

		//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
		void AddPointer(Player* Player,EnemyManager* enemyManger);

		//IObserver
//�ʒm���ɌĂ΂��֐�
		void Notify(const Telegram<GameMessageType>& telegram)  override;

	private:
		//���݂̃J����
		ICamera* m_currentState;
		//TPS�J����
		std::unique_ptr<WataLib::TPS_Camera> m_tpsCamera;
		//�Q�[���I���J����
		std::unique_ptr<WataLib::GameEndCamera> m_endCamera;
		//�v���C��
		Player* m_player;


	};
}
