#pragma once
#ifndef IBOOMERANGSTATE_DEFINED
#define IBOOMERANGSTATE_DEFINED

// IBoomerangState�C���^�t�F�[�X���`����(GOF State�p�^�[��)
class IBoomerangState
{
public:
	virtual ~IBoomerangState() = default;
	// ����������
	virtual void Initialize() = 0;

	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	//��Ԃɓ�������
	virtual void Enter() = 0;
	//��Ԃ𔲂�����
	virtual void Exit() = 0;

	virtual DirectX::SimpleMath::Matrix GetMatrix() = 0 ;
};

#endif		// IBOOMERANGSTATE_DEFINED
