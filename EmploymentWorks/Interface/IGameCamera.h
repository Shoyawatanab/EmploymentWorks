#pragma once
#ifndef ICameCamera_DEFINED
#define ICameCamera_DEFINED

// ICameCamera�C���^�t�F�[�X���`����(GOF State�p�^�[��)
class IGameCamera
{
public:

	// ����������
	virtual void Initialize() = 0;

	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;

	//��Ԃɓ�������
	virtual void Enter() = 0;
	//��Ԃ𔲂�����
	virtual void Exit() = 0;

	virtual const DirectX::SimpleMath::Matrix& GetViewMatrix() = 0;



};

#endif		// ICameCamera_DEFINED
