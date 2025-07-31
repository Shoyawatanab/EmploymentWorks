#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Scene/SceneMessages.h"

class Canvas;
class Image;

class BoomerangThrowUI :public Actor
{
public:
	//������UI
	//���W
	static constexpr DirectX::SimpleMath::Vector3 RIGHT_UI_POSITION ={1180, 550, 0};
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 RIGHT_UI_SCALE = { 0.3f, 0.3f, 0 };
	//�E����UI
	//���W
	static constexpr DirectX::SimpleMath::Vector3 LEFT_UI_POSITION = { 1180, 630, 0 };
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 LEFT_UI_SCALE = { 0.3f, 0.3f, 0 };

	//�ړ���
	static constexpr DirectX::SimpleMath::Vector3 OFFSET = { -50, 0, 0 };


public:
	//�R���X�g���N
	BoomerangThrowUI(Canvas* canvas);
	//�f�X�g���N�^
	~BoomerangThrowUI();

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);


private:
	//������
	Image* m_leftThrow;
	//�E����
	Image* m_rightThrow;

};