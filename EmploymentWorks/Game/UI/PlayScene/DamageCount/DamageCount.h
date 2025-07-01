#pragma once
#include "GameBase/Actor.h"

class Canvas;
class NumberUI;
class Image;

class DamageCount : public Actor
{
public:

	//�w�i�̑傫��
	static constexpr DirectX::SimpleMath::Vector3 BACKGROUND_SCALE = { 0.1f,0.1f,0.0f };
	//�\���Ԋu
	static constexpr float SPACING = 20.0f;
	//�ő�\����
	static constexpr int MAXDIGITS = 3;

	//�\������
	static constexpr float DISPLAYTIME = 0.5f;

public:
	//�R���X�g���N�^
	DamageCount(Canvas* canvas);
	//�f�X�g���N�^
	~DamageCount() override;
	// �P�̍X�V
	void UpdateActor(const float& deltaTime);

	//�A�N�e�B�u�ɂȂ������ɌĂ΂��֐�
	void OnEnable() override;
	//��A�N�e�B�u�ɂȂ������ɌĂ΂��֐�
	void OnDisable() override;

	//�_���[�W�̃Z�b�g
	void SetDamage(int damage);

private:
	//����
	float m_time;
	//�w�i
	Image* m_backGraund;
	//�ۑ��z��@�ő包����������
	std::vector<NumberUI*> m_numbers;
	//�g�p�z��
	std::vector<NumberUI*> m_usedNumbers;
};