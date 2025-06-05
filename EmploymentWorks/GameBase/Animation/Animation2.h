#pragma once
#include "GameBase/Actor.h"
#include <string>
#include <optional>


class Animation2
{
public:

	//�A�j���[�V������Json�ǂݍ��ݐ�p�\����

	struct AnimationKeyFram
	{
		float Time;                                //�o�ߎ���
		std::optional<DirectX::SimpleMath::Vector3>  Scale;
		std::optional< DirectX::SimpleMath::Vector3> Position;	    //�o�ߎ��Ԃɑ΂��Ă̍��W
		std::optional< DirectX::SimpleMath::Vector3> Rotation; 		//�o�ߎ��Ԃɑ΂��Ẳ�]

	};

	struct AnimationData
	{
		float TotalTime;                              //�A�j���[�V�����S�̂̎���
		float Speed;								  //�A�j���[�V�����̐i�s�X�s�[�h
		bool IsLoop;								  //1�A�j���[�V���������[�v�����邩
		std::vector<AnimationKeyFram> FramDatas;	  //�L�[�t���[���̏��@���ԏ��ɕ���ł�����̂Ƃ���

	};

public:

	//�A�j���[�V������
	std::string GetAnimaiionName() { return m_animationName; }

public:
	//�R���X�g���N�^
	Animation2(Actor* owner,std::string animationName, std::string fimePath,std::vector<std::pair<std::string, Transform*>> actors);
	//�f�X�g���N�^
	~Animation2();

	void Update(const float& deltaTime);

	//�A�j���[�V�����̍Đ�
	void PlayAnimation();

private:

	//�A�j���[�V�������̓ǂݍ���
	void LoadData(std::string finePath);

private:
	//���L��
	Actor* m_ower;

	//�A�j���[�V������
	std::string m_animationName;

	//�A�j���[�V�����w����I�u�W�F�N�g
	std::vector<std::pair<std::string ,Transform*>> m_actors;
	//���[�v
	bool m_isLoop;
	//
	float m_totalTime;
	//
	float m_speed;


};
