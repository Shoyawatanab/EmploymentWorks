/*
	1�̃p�[�c�ɑ΂���A�j���[�V�������s���N���X
*/

#pragma once
#include "GameBase/Actor.h"

class Animation
{
public:
	//�L�[�t���[���A�j���[�V�����\����
	struct KeyFram
	{
		float Time;                             //�o�ߎ���
		DirectX::SimpleMath::Vector3 Data;	    //�o�ߎ��Ԃɑ΂��Ẵf�[�^
	};

public:
	//�A�j���[�V�����S�̂̎��Ԃ̃Z�b�g
	void SetAnimationTotalTime(const float& time) { m_animationTotalTime = time; };

public:
	//�R���X�g���N�^
	Animation(Actor* owner);
	//�f�X�g���N�^
	~Animation();
	//�X�V����
	void Update(const float& animationTime);
	//���W�L�[�t���[���̒ǉ�
	void AddPositionData(float framTime,DirectX::SimpleMath::Vector3 position);
	//��]�L�[�t���[���̒ǉ�
	void AddRotateData(float framTime,DirectX::SimpleMath::Vector3 rotae);
	//���Z�b�g
	void Reset();
	//�f�[�^�̕��ёւ�
	void DataSort();


private:
	//���W�̕��ёւ�
	void PositionSort();
	//��]�̕��ёւ�
	void RotateSort();

	//���W�̍X�V
	void PositionUpdate(const float& animationTime);
	//��]�̍X�V
	void RotationUpdate(const float& animationTime);


private:
	//���L��
	Actor* m_actor;
	//���W�̃f�[�^
	std::pair<int, std::vector<KeyFram>> m_positoinData;
	//��]�̃f�[�^
	std::pair<int, std::vector<KeyFram>> m_rotateData;
	//���W�̍X�V�����邩
	bool m_isPositionUpdate;
	//��]�̍X�V�����邩
	bool m_isRotateUpdate;
	//�A�j���[�V�����S�̂̎���
	float m_animationTotalTime;
	//�I�u�W�F�N�g�̏������W
	DirectX::SimpleMath::Vector3 m_initialPosition;
	//�I�u�W�F�N�g�̏�����]
	DirectX::SimpleMath::Quaternion m_initialRotate;
	//�I�u�W�F�N�g�̏����傫��
	DirectX::SimpleMath::Vector3 m_initialScale;

};