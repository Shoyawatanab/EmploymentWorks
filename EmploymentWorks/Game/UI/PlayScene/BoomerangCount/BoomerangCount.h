#pragma once
#include "GameBase/Actor.h"
#include "GameBase//Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Canvas;
class Image;


class BoomerangCount : public Actor , public IObserver<SceneMessageType>
{

	//UI�S�̂̑傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 0.1f,0.1f,0.0f };
	//UI�S�̂̍��W
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 180.0f,650.0f,0.0f };
	//�I�t�Z�b�g
	static constexpr DirectX::SimpleMath::Vector3 OFFSET_POSITION = { 120.0f,0.0f,0.0f };
	//�u�[������UI�P�̂̑傫��
	static constexpr DirectX::SimpleMath::Vector3 BOOMERANG_SCALE = { 0.1f,0.1f,1.0f };

	

public:
	//�R���X�g���N�^
	BoomerangCount(Canvas* canvas);
	//�f�X�g���N�^
	~BoomerangCount() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas)  override;

private:

	std::vector<Image*> m_boomerangUI;

};
