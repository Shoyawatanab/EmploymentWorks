/*
	�N���X��     : BossHp
	����         : �{�XHP��UI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;

class BossHp : public Actor 
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITION{640, 50.5, 0};
	//�w�i�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 BACKGRAUND_SCALE{1, 0.9, 1};
	//���W
	static constexpr DirectX::SimpleMath::Vector3 HP_BAR_SCALE{1, 0.85, 1};

	//�A�j���[�V�����ő厞��
	static constexpr float ANIMATION_MAX_TIME{ 0.2f };

public:
	//�R���X�g���N�^
	BossHp(Canvas* canvas);
	//�f�X�g���N�^
	~BossHp() override ;

	// �P�̍X�V
	void UpdateActor(const float& deltaTime) override;


	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);


private:
	//�w�i
	Image* m_backGraund;
	//HP�o�[
	Image* m_hpBar;
	//�ԐF��HP�o�[
	Image* m_redHpBar;

	//���݂̊���
	float m_currentRatio;

	//�̊���
	float m_startRatio;

	//���݂̊���
	float m_endtRatio;

	//�A�j���[�V���������邩
	bool m_isAnimation;

	//�A�j���[�V��������
	float m_animationTime;


};

