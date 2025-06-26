#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Canvas;
class Image;

class PlayerHp : public Actor , public IObserver<SceneMessageType>
{
public:

	//UI�S�̂̑傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 1.0f,1.0f,0.0f };
	//UI�S�̂̍��W
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 180.0f,550.0f,0.0f };
	//�I�t�Z�b�g
	static constexpr DirectX::SimpleMath::Vector3 OFFSET_POSITION = { 120.0f,0.0f,0.0f };
	//�n�[�g�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 HEART_SCALE = { 0.5f,0.5f,100.4f };

public:
	//�R���X�g���N�^
	PlayerHp(Canvas* canvas);
	//�f�X�g���N�^
	~PlayerHp() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas) override;


private:

	std::vector<Image*> m_heart;

};