/*
	�N���X��     : BirdEnemyHP
	����         : ���G��HP��UI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"


class Canvas;
class Image;

class BirdEnemyHP : public Actor 
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 OFFSET_POSITION{0, 1.0, 0};
	//�w�i�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 BACKGRAUND_SCALE{1, 0.9, 1};
	//���W
	static constexpr DirectX::SimpleMath::Vector3 HP_BAR_SCALE{1, 0.85, 1};

	//�A�j���[�V�����ő厞��
	static constexpr float ANIMATION_MAX_TIME{ 0.2f };

public:

	
	//�����̓o�^
	void SetRatio(float ration);

public:
	//�R���X�g���N�^
	BirdEnemyHP(Canvas* canvas,Actor* owner);
	//�f�X�g���N�^
	~BirdEnemyHP() override ;

	// �P�̍X�V
	void UpdateActor(const float& deltaTime) override;


private:

	//�w�i
	Image* m_backGraund;
	//HP�o�[
	Image* m_hpBar;
	//�ԐF��HP�o�[
	Image* m_redHpBar;

	//���L��
	Actor* m_owner;

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

