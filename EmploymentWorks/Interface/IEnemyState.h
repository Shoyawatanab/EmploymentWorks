#pragma once
#ifndef IEnemyState_DEFINED
#define IEnemyState_DEFINED

// IEnemyState�C���^�t�F�[�X���`����(GOF State�p�^�[��)
class IEnemyState
{
public:
	virtual ~IEnemyState() = default;
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

#endif		// IEnemyState_DEFINED
