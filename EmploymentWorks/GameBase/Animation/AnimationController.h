/*
�����̃A�j���[�^�[���Ǘ�����N���X
*/
#pragma once
#include <unordered_map>

class Animator;
class Actor;

class AnimationController
{
public:
	//�A�j���[�V�����̎��s���
	enum class ExecutionState
	{
		NONE        
		,PLAY       //�ʏ�Đ�
		,TRIIGER	//�P�񂾂����s
		,FLOAT		//
	};

	//��ԑJ�ڂ̃t���[
	enum class TransitionState
	{
		UNIDIRECTIONAL       //�Е���
		, BIDIRECTIONAL      //�o����
	};

	enum  class FloatState
	{
		Greater   //�傫��
		,Less	  //������
	};



	struct FloatParameter
	{
		std::string  FromName;
		std::string  ToName;
		FloatState   State;
		float        Value;
	};

public:
	//�R���X�g���N�^
	AnimationController();
	//�f�X�g���N�^
	virtual ~AnimationController();
	//�X�V����
	void Update(const float& deltaTime);

	//�A�j���[�V�����̒ǉ�
	void AddAnimatoin(Actor* owner,std::string animationName, std::string filePath,std::vector<std::pair<std::string,Actor*>>, bool isNormal = false);
	//�g���K�[��ԑJ�ڃt���[�̍쐬
	void CreateTriggerTransition(const std::string& fromAnimationName,const std::string& toAnimationName , const std::string& connectionName);
	//Float��ԑJ�ڃt���[�̍쐬
	void CreateFloatTransition(const std::string& fromAnimationName, const std::string& toAnimationName, const std::string& connectionName,const float& value, FloatState state);
	//AnyState����̃g���K�[��ԑJ�ڃt���[�̍쐬 
	void CreateAnyStateToTriggerTransition(const std::string& toAnimationName, const std::string& connectionName);
	//AnyState�����Float��ԑJ�ڃt���[�̍쐬
	void CreateAnyStateToFloatTransition(const std::string& toAnimationName, const std::string& connectionName, const float& value, FloatState state);
	//�J�ڃp�����[�^�[�̍쐬    ��ԑJ�ږ��@���
	void CrateTransitionParameter(std::unordered_map<std::string, ExecutionState> parameters) { m_transitionParamter = parameters; };

	//�A�j���[�V�����̍Đ��@�@�I����Loop�o�Ȃ��Ȃ�~�܂�
	void Play(const std::string& animationName);
	//�A�j���[�V�����̐؂�ւ��@�I����ʏ�ɖ߂�
	void SetTrigger(const std::string& connectionName);
	//�A�j���[�V�����̐؂�ւ��@�΂����傫���ꍇ�̂ݕύX�@
	void SetFloat(const std::string& connectionName,const float& value);

private:

	//��ԑJ�ڃ��X�g�ɒǉ�
	void AddTransitionList(std::string state1, std::string state2);
	//�A�j���[�V�����̐؂�ւ����s���Ă��������@true: �悢  false:�_��
	bool IsChangeAnimation(const std::string& animationName);
	//�J�ږ����p�����[�^�[�ɂ��邩
	bool IsFindParameter(const std::string& connectionName);
	//�g���K�[�̎��s���ł��邩�̔���
	bool CheckTrigger(const std::string& connectionName);
	//Float�̑J�ڃt���[�����邩�̔���
	bool CheckFloatTransition(const std::string& connectionName,const float& value);
	//Float�̒l�ɂ�锻��
	bool CheckFloatValue(const std::string& connectionName,const float& value);

	//�A�j���[�V�����̐؂�ւ�
	void ChangeAnimation(Animator* animatior);
private:

	//���s�A�j���[�V����
	Animator* m_currentAnimation;
	//�ʏ�A�j���[�V����
	Animator* m_normalAnimation;
	//�A�j���[�V�����̊i�[�ϐ�
	std::unordered_map<std::string , std::unique_ptr<Animator>> m_animations;

	//��ԑJ�ڂ̕ۑ�
	std::unordered_map<std::string,std::vector<std::string>> m_stateTransitionList;

	//���s���
	ExecutionState m_state;
	//�J�ڃp�����[�^�[
	std::unordered_map<std::string, ExecutionState> m_transitionParamter;
	//�g���K�[�J�ڃ��X�g
	std::unordered_map<std::string, std::pair<std::string, std::string>> m_triggerTransitionList;
	//�t���[�g�J�ڃ��X�g
	std::unordered_map<std::string, FloatParameter> m_floatTransitionList;

};