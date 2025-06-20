#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Image;

class PlayerHp : public Actor
{
public:

	//UI�S�̂̑傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 10.0f,10.0f,0.0f };
	//UI�S�̂̍��W
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 180.0f,550.0f,0.0f };
	//�I�t�Z�b�g
	static constexpr DirectX::SimpleMath::Vector3 OFFSET_POSITION = { 100.0f,0.0f,0.0f };
	//�n�[�g�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 HEART_SCALE = { 70.0f,70.0f,100.4f };

public:
	//�R���X�g���N�^
	PlayerHp(Canvas* canvas);
	//�f�X�g���N�^
	~PlayerHp();

private:

	std::vector<Image*> m_heart;

};