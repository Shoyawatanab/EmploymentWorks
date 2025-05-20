#pragma once
#include <unordered_map>
#include "Libraries/WataLib/Json.h"


namespace WataLib
{
	class Animation final
	{
	public:

		struct KeyFram
		{
			float Time;                                //�o�ߎ���
			DirectX::SimpleMath::Vector3 Data;
		};

		struct AnimationData
		{
			std::string TypeName;
			float TotalTime;                              //�A�j���[�V�����S�̂̎���
			float Speed;								  //�A�j���[�V�����̐i�s�X�s�[�h
			bool IsLoop;								  //1�A�j���[�V���������[�v�����邩
			std::vector<KeyFram> Position;
			std::vector<KeyFram> Rotation;

		};

		struct FromTo
		{
			int Index = 0;
			KeyFram keyFrame;
		};

	public:

		const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; };

		const DirectX::SimpleMath::Quaternion& GetRotation() { return m_rotation; }

	public:
		//�R���X�g���N�^
		Animation();
		//�f�X�g���N�^
		~Animation();
		//�X�V����
		bool Update(const float& elapsedTime);
		//���W�̃A�j���[�V�����̍X�V
		void PositionUpdate(const float& elapsedTime);
		//��]�̃A�j���[�V�����̍X�V
		void RotationUpdate(const float& elapsedTime);

		//�A�j���[�V�������̓o�^
		void SetAnimationData(const std::string& animationType, const WataLib::Json::AnimationData& data, bool isNormalAnimation = false);
		//���s�A�j���[�V�����̐؂�ւ�
		void ChangeAnimation(const std::string& animationType);
		//���s�A�j���[�V�����̏��̏�����
		void InitializAnimationData(const std::string& animationType);
		//���W�̃L�[�t���[���̐؂�ւ�
		void ChangePositionKeyFrame();
		//��]�̃L�[�t���[���̐؂�ւ�
		void ChangeRotationKeyFrame();


	private:
		//�A�j���[�V�����f�[�^
		std::unordered_map<std::string, AnimationData> m_animationData;
		//���s���̃A�j���[�V�����f�[�^
		AnimationData m_currentAnimationData;
		//���W
		DirectX::SimpleMath::Vector3 m_position;
		//��]
		DirectX::SimpleMath::Quaternion m_rotation;
		//�y�A���W
		std::pair<FromTo, FromTo> m_fromToPosition;
		//�y�A��]
		std::pair<FromTo, FromTo> m_fromToRotation;
		//����
		float m_time;
		//�ʏ�A�j���[�V����
		std::string m_normalAnimationType;

	};
}

//animationData�ɂ͍Œ�ł��Q�̃f�[�^���K�v�@�Ȃ��ꍇ�ł��A�j���[�V�����S�̂̂͂��߂Ƃ����łO�������̒l�����Ă���


