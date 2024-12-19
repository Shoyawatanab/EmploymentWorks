#pragma once
#ifndef IEnemyState_DEFINED
#define IEnemyState_DEFINED

// IEnemyState�C���^�t�F�[�X���`����(GOF State�p�^�[��)
class IEnemy
{
public:
	virtual ~IEnemy() = default;
	// ����������
	virtual void Initialize() = 0;

	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	//�`��
	virtual void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj) = 0;

};

#endif		// IEnemyState_DEFINED
