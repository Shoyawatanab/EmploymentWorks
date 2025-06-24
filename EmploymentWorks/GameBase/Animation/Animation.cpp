#include "pch.h"
#include "Animation.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="owner">���L��</param>
Animation::Animation(Actor* owner)
	:
	m_actor{owner}
	,m_isPositionUpdate{false}
	,m_isRotateUpdate{false}
	,m_animationTotalTime{}
	,m_initialPosition{}
	,m_initialRotate{}
	,m_initialScale{}
{

	//���L�҂̏�����Ԃ��擾
	auto transform = m_actor->GetTransform();
	m_initialPosition = transform->GetPosition();
	m_initialRotate = transform->GetRotate();
	m_initialScale = transform->GetScale();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Animation::~Animation()
{
	m_positoinData.second.clear();
	m_rotateData.second.clear();
}

 
/// <summary>
/// �X�V����
/// </summary>
/// <param name="animationTime">�A�j���[�V�����̌o�ߎ���</param>
void Animation::Update(const float& animationTime)
{
	//���W�̍X�V���s����
	if (m_isPositionUpdate)
	{
		//���W
		PositionUpdate(animationTime);

	}
	//��]�̍X�V���s����
	if (m_isRotateUpdate)
	{
		//��]
		RotationUpdate(animationTime);

	}

}

/// <summary>
/// ���W�f�[�^�̒ǉ�
/// </summary>
/// <param name="framTime">�t���[������</param>
/// <param name="position">���W</param>
void Animation::AddPositionData(float framTime, DirectX::SimpleMath::Vector3 position)
{
	using namespace DirectX::SimpleMath;


	//�t���[���̒ǉ�
	KeyFram fram = { framTime,position };
	m_positoinData.second.push_back(fram);

	//�X�V���s������L����
	m_isPositionUpdate = true;
	
}

/// <summary>
/// ��]�f�[�^�̒ǉ�
/// </summary>
/// <param name="framTime">�t���[������</param>
/// <param name="rotate">��]</param>
void Animation::AddRotateData(float framTime, DirectX::SimpleMath::Vector3 rotate)
{

	//�t���[���̒ǉ�
	KeyFram fram = { framTime,rotate };
	m_rotateData.second.push_back(fram);

	//�X�V���s������L����
	m_isRotateUpdate = true;

}

/// <summary>
/// ���Z�b�g
/// </summary>
void Animation::Reset()
{
	m_positoinData.first = 0;
	m_rotateData.first = 0;

	//���[�J����]�̍X�V
	m_actor->GetTransform()->SetPosition(m_initialPosition);
	m_actor->GetTransform()->SetRotate(m_initialRotate);

}

/// <summary>
/// �f�[�^�̕��ёւ�
/// </summary>
void Animation::DataSort()
{

	//���W�̕��ёւ�
	PositionSort();
	//��]�̕��ёւ�
	RotateSort();


}
/// <summary>
/// ���W�̕��ёւ�
/// </summary>
void Animation::PositionSort()
{
	using namespace DirectX::SimpleMath;

	//�f�[�^���Ȃ����
	if (m_positoinData.second.empty())
	{
		return;
	}
	//�P�ȏ�Ȃ�
	if (m_positoinData.second.size() > 1)
	{
		//��]����Time�ŏ����ɕ��ёւ�
		std::sort(m_positoinData.second.begin(), m_positoinData.second.end(),
			[](const KeyFram& a, const KeyFram& b)
			{
				return a.Time < b.Time;
			});
	}


	//�͂��߂�0.0f�ł͂��ꍇ
	if (m_positoinData.second[0].Time != 0.0f)
	{
		//���߂Ƀ[��������
		m_positoinData.second.insert(m_positoinData.second.begin(), { 0.0f,Vector3::Zero });
	}
	//�I��肪�A�j���[�V�������ԂłȂ��ꍇ
	if (m_positoinData.second[m_positoinData.second.size() - 1].Time != m_animationTotalTime)
	{
		//�I���Ƀ[��������
		m_positoinData.second.push_back({ m_animationTotalTime,Vector3::Zero });

	}

}

/// <summary>
/// ��]�̕��ёւ�
/// </summary>
void Animation::RotateSort()
{

	using namespace DirectX::SimpleMath;

	//�f�[�^���Ȃ����
	if (m_rotateData.second.empty())
	{
		return;
	}
	//�P�ȏ�Ȃ�
	if (m_rotateData.second.size() > 1)
	{
		//��]����Time�ŏ����ɕ��ёւ�
		std::sort(m_rotateData.second.begin(), m_rotateData.second.end(),
			[](const KeyFram& a, const KeyFram& b)
			{
				return a.Time < b.Time;
			});
	}


	//�͂��߂�0.0f�ł͂��ꍇ
	if (m_rotateData.second[0].Time != 0.0f)
	{
		//���߂Ƀ[��������
		m_rotateData.second.insert(m_rotateData.second.begin(), { 0.0f,Vector3::Zero });


	}
	//�I��肪�A�j���[�V�������ԂłȂ��ꍇ
	if (m_rotateData.second[m_rotateData.second.size() - 1].Time != m_animationTotalTime)
	{
		//�I���Ƀ[��������
		m_rotateData.second.push_back({ m_animationTotalTime,Vector3::Zero });

	}

	

}

/// <summary>
/// ���W�̍X�V
/// </summary>
void Animation::PositionUpdate(const float& animationTime)
{
	using namespace DirectX::SimpleMath;

	//�Y����
	int index = m_positoinData.first;

	//���߂̎���
	float startTime = m_positoinData.second[index].Time;
	//�I���̎���
	float endTime = m_rotateData.second[index + 1].Time;
	//���߂̃f�[�^
	Vector3 startData = m_positoinData.second[index].Data;
	//�I���̃f�[�^
	Vector3 endData = m_positoinData.second[index + 1].Data;



	//����
	float ratio = 0;
	//�O�����ł͌v�Z�����Ȃ�����
	if (endTime != startTime)
	{
		ratio = (animationTime - startTime) / (endTime - startTime);
	}
	//������1�𒴂��Ȃ��悤��
	ratio = std::min(ratio, 1.0f);

	//��]
	Vector3 position = Vector3::SmoothStep(startData, endData, ratio);

	//���[�J�����W�̍X�V
	m_actor->GetTransform()->SetPosition(m_initialPosition + position);

	//�t���[���̐؂�ւ�
	if (animationTime >= endTime)
	{
		m_positoinData.first++;
		m_positoinData.first = m_positoinData.first % m_positoinData.second.size();
	}




}

/// <summary>
/// ��]�̍X�V
/// </summary>
void Animation::RotationUpdate(const float& animationTime)
{
	using namespace DirectX::SimpleMath;
	
	//�Y����
	int index = m_rotateData.first;

	//���߂̎���
	float startTime = m_rotateData.second[index].Time;
	//�I���̎���
	float endTime = m_rotateData.second[index + 1].Time;
	//���߂̃f�[�^
	Vector3 startData = m_rotateData.second[index].Data;
	//�I���̃f�[�^
	Vector3 endData = m_rotateData.second[index + 1].Data;


	//�f�[�^�����]���쐬
	Quaternion startRotation = Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(startData.y),
		DirectX::XMConvertToRadians(startData.x),
		DirectX::XMConvertToRadians(startData.z)
	);
	Quaternion endRotation = Quaternion::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(endData.y),
		DirectX::XMConvertToRadians(endData.x),
		DirectX::XMConvertToRadians(endData.z)
	);

	//����
	float ratio = 0;
	//�O�����ł͌v�Z�����Ȃ�����
	if (endTime != startTime)
	{
		ratio = (animationTime - startTime) / (endTime - startTime);
	}

	//������1�𒴂��Ȃ��悤��
	ratio = std::min(ratio, 1.0f);

	//��]
	Quaternion rotation = Quaternion::Slerp(startRotation, endRotation, ratio);

	//���[�J����]�̍X�V
	m_actor->GetTransform()->SetRotate(m_initialRotate *  rotation);

	//�t���[���̐؂�ւ�
	if (animationTime >= endTime)
	{
		m_rotateData.first++;
		m_rotateData.first =  m_rotateData.first % m_rotateData.second.size();
	}

}

