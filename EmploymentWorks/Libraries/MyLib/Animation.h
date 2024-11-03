#pragma once
#include <unordered_map>




class Animation final 
{
public:

	enum AnimationState
	{
		None,
		Running,   //���s��
		End        //�I��

	};

	//�A�j���[�V�����̍Đ����
	enum AnimationPlayBackType
	{
		Loop,   //���[�v
		Once,   //��񂾂�
	}; 

	struct AnimationKeyFrame
	{
		//DirectX::SimpleMath::Vector3 Scale;        //�傫��
		//DirectX::SimpleMath::Vector3 Position;      //���W
		DirectX::SimpleMath::Quaternion Rotation;   //��]�@
		float Time;                                 //�������鎞��
	};

public:

	Animation();
	~Animation();

	AnimationState Update(float elapsdTime);

public:

	void SetAnimation(std::vector<AnimationKeyFrame> animations, AnimationPlayBackType PlayBackType);
	//�A�j���[�V�����̉�]�̎擾
	DirectX::SimpleMath::Quaternion GetAnimationRotate() { return m_animationRotate; }

	void ResetAnimation();
private:

	
	//�A�j���[�V�����̍Đ����
	AnimationPlayBackType m_playBackType;
	//�A�j���[�V����
	std::vector<AnimationKeyFrame> m_animation;
	//�g�[�^������
	float m_totalTime;
	//���s���ɃA�j���[�V�����̃C���f�b�N�X
	int m_keyFrameIndex;
	//���s���A�j���[�V�����̉�]
	DirectX::SimpleMath::Quaternion m_animationRotate;
	//�A�j���[�V�����̏��
	AnimationState m_state;
};
