/*
	�P�̃A�j���[�V�����ɑ΂��ăp�[�c�̊Ǘ����s���N���X
*/
#pragma once
#include "GameBase/Actor.h"
#include <string>

class Transform;
class Animation;

class Animator
{
public:

	//�A�j���[�V������
	const  std::string& GetAnimaiionName() { return m_animationName; }
	//���[�v���邩�̎擾�@ture: ���[�v����@false :���[�v�Ȃ�
	bool GetIsLoop() const { return m_isLoop; }
	//�A�j���[�V�������I����Ă��邩�@true �I����Ă���@false �I����Ă��Ȃ�
	bool GetIsEnd() const { return m_isEnd; }

public:
	//�R���X�g���N�^
	Animator(Actor* owner
		,const std::string& animationName
		,const std::string& fimePath
		,std::vector<std::pair<std::string, Actor*>> actors);
	//�f�X�g���N�^
	~Animator();
	//�X�V�����@ture: ���s���@false :�I��
	bool Update(const float& deltaTime);

	//�A�j���[�V�����̍Đ�
	void PlayAnimation();
	//�Ď��s
	void Rerun();

private:

	//�A�j���[�V�������̓ǂݍ���
	void LoadData(std::string finePath);



private:
	//���L��
	Actor* m_ower;

	//�A�j���[�V������
	std::string m_animationName;
	//���[�v
	bool m_isLoop;
	//�A�j���[�V�����S�̂̎���
	float m_animationTotalTime;
	//�A�j���[�V�����X�s�[�h
	float m_speed;
	//�p�[�c���Ƃ̃f�[�^
	std::unordered_map<std::string,std::unique_ptr<Animation>> m_partsData;
	//�A�j���[�V�����̌o�ߎ���
	float m_animationTime;
	//�A�j���[�V�������I����Ă��邩
	bool m_isEnd;
};
