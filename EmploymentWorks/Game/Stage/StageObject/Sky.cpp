/*
	@file	Sky.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Sky.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>



/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
Sky::Sky(CommonResources* resources
	, DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation)
	:
	m_model{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Sky::~Sky()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void Sky::Initialize()
{




}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void Sky::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{


}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Sky::Update(const float& elapsedTime)
{




}











