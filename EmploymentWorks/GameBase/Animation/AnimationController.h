#pragma once
#include <unordered_map>

class Animation2;

class AnimationController
{
public:
	//�A�j���[�V�����̎��s���
	enum class ExecutionState
	{
		NONE        //�ʏ�
		,TRIIGER	//�P�񂾂����s
		,FLOAT		//
	};

	//��ԑJ�ڂ̃t���[
	enum class TransitionState
	{
		UNIDIRECTIONAL       //�Е���
		, BIDIRECTIONAL      //�o����
	};

public:
	//�R���X�g���N�^
	AnimationController();
	//�f�X�g���N�^
	virtual ~AnimationController();
	//�X�V����
	void Update(const float& deltaTime);

	//�A�j���[�V�����̒ǉ�
	void AddAnimatoin(std::unique_ptr<Animation2> animatino);
	//�A�j���[�V�����̐؂�ւ�
	void SetTrigger(std::string animationName);
	//�A�j���[�V�����̐؂�ւ��@�΂����傫���ꍇ�̂ݕύX
	void SetFloat(std::string animationName,float value);
	//��ԑJ�ڃt���[�̍쐬
	void CreateTransitionFlow(std::string state1, std::string state2,TransitionState transitionState);
private:

	//��ԑJ�ڃ��X�g�ɒǉ�
	void AddTransitionList(std::string state1, std::string state2);

private:

	//�f�t�H���g�A�j���[�V����

	//���s�A�j���[�V����
	Animation2* m_currentAnimation;
	//�A�j���[�V�����̊i�[�ϐ�
	std::vector<std::unique_ptr<Animation2>> m_animations;

	//��ԑJ�ڂ̕ۑ�
	std::unordered_map<std::string,std::vector<std::string>> m_stateTransitionList;



};