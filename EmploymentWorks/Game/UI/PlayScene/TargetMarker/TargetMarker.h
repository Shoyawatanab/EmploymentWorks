#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Canvas;
class Image;

class TargetMarker : public Actor, public IObserver<SceneMessageType>
{
public:
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE {0.3f, 0.3f, 200.0f};
	//�^�[�Q�b�g�̒��S����̋���
	static constexpr float RANGE{ 200.0f };
public:

	//�\���Ă��邩 true:LockOn���   false:����Ȃ�
	bool GetIsGetLockOn() { return m_isLockOn; }
	//�^�[�Q�b�g���W�̎擾
	DirectX::SimpleMath::Vector3 GetTargetPosition() { return m_targetPosition; }
	
public:
	//�R���X�g���N�^
	TargetMarker(Canvas* canvas,std::vector<Actor*> targets);
	//�f�X�g���N�^
	~TargetMarker() override;
	// �P�̍X�V
	void UpdateActor(const float& deltaTime) override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas) override;


private:
	//�͈͓����ǂ���������
	DirectX::SimpleMath::Vector2 FilterWithinRange();


	

private:
	//�}�[�J�[
	Image* m_marker;
	//�^�[�Q�b�g�z��
	std::vector<Actor*> m_targets;
	//
	DirectX::SimpleMath::Vector3 m_targetPosition;
	//�\���Ă��邩
	bool m_isGetReady;
	//���b�N�I����Ԃ�
	bool m_isLockOn;

};