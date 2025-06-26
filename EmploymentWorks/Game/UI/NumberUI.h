#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Image;

class NumberUI : public Actor
{
public:
	//�P���̉���
	static constexpr float DIGITWIDTH{0.1f}
	;
public:
	//�R���X�g���N�^
	NumberUI(Canvas* canvas);
	//�f�X�g���N�^
	~NumberUI() override;
	//�����̓o�^
	void SetNumber(int number);

private:

	//�ԍ��C���[�W
	Image* m_number;

};

