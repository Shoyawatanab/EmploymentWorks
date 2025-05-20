/*
	@file	BarrierShrink.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BarrierShrink.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>
#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/Params.h"
#include "Game/Observer/Messenger.h"

#include "Game/Enemys/BossEnemy/Barrier/Barrier.h"
#include "Game/Enemys/BossEnemy/Barrier/State/BarrierStateMachine.h"


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="barrier">�o���A</param>
BarrierShrink::BarrierShrink(CommonResources* resources
	, Barrier* barrier)
	:
	m_time{}
	,m_barrier{barrier}
{
	UNREFERENCED_PARAMETER(resources);

}



/// <summary>
/// �f�X�g���N�^
/// </summary>
BarrierShrink::~BarrierShrink()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BarrierShrink::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);

}

void BarrierShrink::Update(const float& elapsedTime)
{

	using namespace DirectX::SimpleMath;

	float ratio = m_time / 0.35f;

	ratio = std::min(ratio, 1.0f);

	Vector3 scale = Vector3::Lerp(Barrier::SCALE,Vector3::Zero, ratio);

	m_barrier->SetLocalScale(scale);

	m_time += elapsedTime;

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BarrierShrink::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BarrierShrink::Enter()
{

	m_time = 0;

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BarrierShrink::Exit()
{
}






