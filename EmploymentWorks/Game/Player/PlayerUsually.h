/*
* �v���C���̏펞�̍X�V�̃N���X
*/
#pragma once
#include"Game/Interface/IObserver.h"

// �O���錾
class CommonResources;
class Player;

namespace WataLib
{
	class TPS_Camera;
}

class PlayerUsually  : public IObserver<GameMessageType>
{
public:
	//�R���X�g���N�^
	PlayerUsually() ;
	//�f�X�g���N�^
	~PlayerUsually();
	//
	void AddPointer(Player* player, WataLib::TPS_Camera* tpsCamera);

	//������
	void Initialize(CommonResources* resources);
	// �X�V����
	void Update(const float& elapsedTime);
	//����
	void Move(const float& elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);
	//��]
	void Rotation(const float& elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);

	//IObserver
	//�ʒm���ɌĂ΂��֐�
	void Notify(const Telegram<GameMessageType>& telegram)  override;


private:
	//�|�C���^
	//�v���C��
	Player* m_palyer;
	//�J����
	WataLib::TPS_Camera* m_tpsCamera;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	//�\���Ă��邩�ǂ���
	bool m_isGetReady;

};