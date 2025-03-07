/*
	@file	BarrierGenerate.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IState.h"

// �O���錾
class CommonResources;
class Barrier;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

namespace WataLib
{
	class Bounding;

}

class BarrierGenerate : public IState
{
public:




public:
	BarrierGenerate(CommonResources* resources
	, Barrier* barrier);
	
	//�f�X�g���N�^
	~BarrierGenerate() ;

	//������
	void Initialize(CommonResources* resources) ;
	// �X�V����
	void Update(const float& elapsedTime);
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	//��Ԃɓ�������
	void Enter();
	//��Ԃ𔲂�����
	void Exit() ;

private:

	Barrier* m_barrier;

	float m_time;




};
