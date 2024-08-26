#pragma once
/*
	@file	BeamModel.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"

// �O���錾
class CommonResources;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BeamModel 

{
public:

	void SetPos(DirectX::SimpleMath::Vector3 Pos) { m_position = Pos; }

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;

	float m_scale;


public:
	BeamModel();
	~BeamModel() ;

	BeamModel(BeamModel& other);

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position,float scale);
	void Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

private:
};
