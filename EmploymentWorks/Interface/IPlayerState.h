#pragma once
#ifndef IPLAYERSTATE_DEFINED
#define IPLAYERSTATE_DEFINED

// IBoomerangState�C���^�t�F�[�X���`����(GOF State�p�^�[��)
class IPlayerState
{
public:
	virtual ~IPlayerState() = default;
	// ����������
	virtual void Initialize() = 0;

	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	//��Ԃɓ�������
	virtual void Enter() = 0;
	//��Ԃ𔲂�����
	virtual void Exit() = 0;


	virtual void ResetGravity() = 0;

};

#endif		// IBOOMERANGSTATE_DEFINED
