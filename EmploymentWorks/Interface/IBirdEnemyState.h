#pragma once
#ifndef IBIRD_DEFINED
#define IBIRD_DEFINED

// IBoomerangState�C���^�t�F�[�X���`����(GOF State�p�^�[��)
class IBirdEnemyState
{
public:
	virtual ~IBirdEnemyState() = default;
	// ����������
	virtual void Initialize() = 0;

	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	//��Ԃɓ�������
	virtual void Enter() = 0;
	//��Ԃ𔲂�����
	virtual void Exit() = 0;



};

#endif		// IBOOMERANGSTATE_DEFINED
