/*
	�N���X��     : ResultTime
	����         : ���U���g�V�[���̎���UI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"

class Canvas;
class NumberUI;
class TimeSeparator;

class ResultTime : public Actor
{
public:
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 0.65f,0.65f,0.4f };
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 750,310,0 };
	//�����Ԋu
	static constexpr float LETTER_SPACING = 100.0f;

	//�_�ŊԊu
	static constexpr float BLINK_INTERVAL = 1.0f;

public:
	//�R���X�g���N
	ResultTime(Canvas* canvas);
	//�f�X�g���N�^
	~ResultTime() override;

	//�ʃA�b�v�f�[�g
	void UpdateActor(const float& deltaTime) override;


	//���Ԃ̃Z�b�g
	void AddTime(const float& totalSecond);

private:

	//�_��
	void Blink(const float& deltaTime);
	
private:

	//�����z��
	std::vector<NumberUI*> m_numbers;
	//��؂�_
	TimeSeparator* m_separator;

	//����
	float m_time;


};